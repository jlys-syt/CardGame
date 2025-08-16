#include "CardController.h"

 // 通过游戏模型进行构造初始化
CardController::CardController(GameModel gameModel)
    : _gameModel(gameModel), _undoManager(gameModel.getUndoModel()) {}

CardController::~CardController() {}

 // 桌面卡牌匹配，匹配成功，记录状态，处理点击事件
void CardController::clickPlayFieldCard(CardModel& card)
{
    CCLOG(u8"playerfield牌堆触发");
    if (_undoManager.getUndoSize() == 0) // 无手牌
    {
        CCLOG(u8"无手牌");
        return;
    }

    int face1 = static_cast<int>(card.getFaceType());
    // 获得手牌顶部的face
    int face2 = static_cast<int>(getHandCard().getFaceType());
    if (abs(face1 - face2) == 1) { // 相差一，匹配成功
        UndoCardPosition state;
        state.cardId = card.getCardId(); // 回退栈记录新状态
        state.position = card.getPosition();
        state.zone = card.getZone();
        _undoManager.recordState(state);
        moveToHandPos(card);
    }
}

 // 点击堆牌，保存回退信息，进行 move to 手牌位置
void CardController::clickStackCard(CardModel& card) {
    UndoCardPosition state;
    state.cardId= card.getCardId();
    state.position = card.getPosition();
    state.zone = card.getZone();
    _undoManager.recordState(state);
    CardManager* cardManager = getCardManager(card);
    CCLOG(u8"stack牌堆触发");
    moveToHandPos(card);
}

 // 获取最上一张手牌模型
CardModel CardController::getHandCard() {
    UndoCardPosition state;
    if (_undoManager.undo(state)) {
        _undoManager.recordState(state); // state被修改为撤销栈的栈顶卡牌状态
        auto& playfield = _gameModel.getPlayfield(); // 根据 state.cardId 获取 CardModel 模型
        for (const auto& card : playfield) {
            if (card.getCardId() == state.cardId) {
                return card;
            }
        }
        auto& stackfield = _gameModel.getStackfield();
        for (const auto& card : stackfield) {
            if (card.getCardId() == state.cardId) {
                return card;
            }
        }
    }
    return CardModel(cocos2d::Vec2::ZERO, CardSuitType::CST_SPADES, CardFaceType::CFT_ACE); // 异常处理
}

 // 回到老位置
void CardController::moveToOldPos(const UndoCardPosition& state) {
    auto& playField = _gameModel.getPlayfield();
    auto& stackField = _gameModel.getStackfield();

    for (auto card : playField) {
        if (card.getCardId() == state.cardId) { // 查看是否在桌面区域
            CardView* cardView = getCardView(card);
            if (cardView) {
                auto moveTo = cocos2d::MoveTo::create(0.5f, state.position);
                cardView->runAction(moveTo); // move到老位置
                card.setPosition(state.position); // 修改卡牌模型的位置、区域信息
                card.setZone(state.zone);
                cardView->setGlobalZOrder(0);
            }
            return;
        }
    }

    for (auto card : stackField) { // 查看是否在堆区，修改卡牌模型的位置、区域信息， move 到相应位置
        if (card.getCardId() == state.cardId) {
            CardView* cardView = getCardView(card);
            if (cardView) {
                auto moveTo = cocos2d::MoveTo::create(0.5f, state.position);
                cardView->runAction(moveTo);
                card.setPosition(state.position);
                card.setZone(state.zone);
                cardView->setGlobalZOrder(0);
            }
            return;
        }
    }
}

 // 获得卡牌的管理对象
CardManager* CardController::getCardManager(const CardModel& card) {
    CardManager* manager = CardIdManagerMap::getInstance().getCardManager(card.getCardId());
    return manager;
}

 // 前向声明未解决的情况下，解决 CardView 和 CardManager 的循环依赖引起的问题，由 CardIdManagerMap 实例直接获得卡牌视图
CardView* CardController::getCardView(const CardModel& card)
{
    CardView* view = CardIdManagerMap::getInstance().getCardView(card.getCardId()); 
    return view;
}

 // 处理卡牌点击逻辑
void CardController::moveToHandPos(CardModel& card) {
    if (card.getZone() != CardZone::Hand) { // 非手牌自己匹配
        auto oldZone = card.getZone();
        cocos2d::Vec2 newPos(450, 160);
        CardView* cardView = getCardView(card); // 获得卡牌视图，更改属性信息
        card.setZone(CardZone::Hand);
        card.setPosition(newPos);
        if (cardView) {
            CCLOG(u8"移动卡牌，id: %d, %d -> %d", card.getCardId(),oldZone,card.getZone());
            auto moveTo = cocos2d::MoveTo::create(0.5f, newPos); // 移动到手牌区域
            cardView->runAction(moveTo);
            if (_undoManager.getUndoSize() != 0) {
                CardModel& lastCard = getHandCard();
                cardView->setLocalZOrder(getCardView(lastCard)->getLocalZOrder() + 1); // 层级比手牌的最上面一张大
            }
        }
    }
}

 // 处理 backLabel 标签的点击事件
void CardController::handleLabelClick() {
    UndoCardPosition state;
    if (_undoManager.undo(state)) { // state修改为栈顶状态信息
        moveToOldPos(state);
    }
    CCLOG(u8"无回退状态");
}
