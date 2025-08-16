#include "CardController.h"

 // 通过游戏模型进行构造初始化
CardController::CardController(GameModel gameModel)
    : _gameModel(gameModel), _undoManager(gameModel.getUndoModel()) {}

CardController::~CardController() {}

 // 桌面卡牌匹配，匹配成功，记录状态，处理点击事件
bool CardController::selectCardFromPlayefieldAndMatch(CardModel& selectedCard) {
    if (_undoManager.getUndoSize() == 0) {
        return false;
    }
    CardModel bottomCard = getBottomCard();
    CCLOG(u8"playerfield牌堆触发");
    if (isCardMatch(selectedCard, bottomCard)) {  // 匹配成功，记录撤销状态        
        UndoCardPosition state;
        state.cardId = selectedCard.getCardId();
        state.position = selectedCard.getPosition();
        state.zone = selectedCard.getZone();
        _undoManager.recordUndoState(state);
        handleCardClicked(selectedCard); // 处理点击事件
        return true;
    }
    return false;
}

 // 点击堆牌，保存回退信息，进行 move to 手牌位置
void CardController::clickStackCard(CardModel& card) {
    UndoCardPosition state;
    state.cardId= card.getCardId();
    state.position = card.getPosition();
    state.zone = card.getZone();
    _undoManager.recordUndoState(state);
    CardManager* cardManager = getCardManager(card);
    CCLOG(u8"stack牌堆触发");
    handleCardClicked(card);
}

 // 撤销卡牌，退回原位置
bool CardController::undo() {
    UndoCardPosition state;
    if (_undoManager.undo(state)) { // state修改为栈顶状态信息
        moveToOldPos(state);
        return true;
    }
    return false;
}

 // 获取手牌模型,通过回退栈的栈顶卡牌模型获取，与容器数据进行比较，返回 CardModel 模型
CardModel CardController::getBottomCard() {
    UndoCardPosition state;
    if (_undoManager.undo(state)) {
        _undoManager.recordUndoState(state); // state被修改为撤销栈的栈顶卡牌的位置信息
        auto& playfield = _gameModel.getPlayfield();
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
    return CardModel(cocos2d::Vec2::ZERO, CardSuitType::CST_SPADES, CardFaceType::CFT_ACE); // 无回退记录的特殊处理
}

 // 卡牌是否匹配
bool CardController::isCardMatch(const CardModel& card1, const CardModel& card2) {
    int face1 = static_cast<int>(card1.getFaceType());
    int face2 = static_cast<int>(card2.getFaceType());
    return (face1 == face2 + 1) || (face1 == face2 - 1);
}

 // 回到老位置
void CardController::moveToOldPos(const UndoCardPosition& state) {
    auto& playField = _gameModel.getPlayfield();
    auto& stackField = _gameModel.getStackfield();

    for (auto card : playField) { // 查看是否在桌面区域，修改卡牌模型的位置、区域信息， move 到相应位置
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
void CardController::handleCardClicked(CardModel& card) {
    if (card.getZone() != CardZone::Hand) { // 不在手牌区域，获得卡牌视图，移动到手牌区域
        auto oldZone = card.getZone();
        //cocos2d::Vec2 newPos(700, 400);
        cocos2d::Vec2 newPos(450, 160);
        CardView* cardView = getCardView(card);
        card.setZone(CardZone::Hand);
        card.setPosition(newPos);
        if (cardView) {
            CCLOG(u8"移动卡牌，id: %d, %d -> %d", card.getCardId(),oldZone,card.getZone());
            auto moveTo = cocos2d::MoveTo::create(0.5f, newPos);
            cardView->runAction(moveTo);
            if (_undoManager.getUndoSize() != 0) {
                CardModel& lastCard = getBottomCard();
                cardView->setLocalZOrder(getCardView(lastCard)->getLocalZOrder() + 1); // 层级比手牌的最上面一张大
            }
        }
    }
}

 // 处理 backLabel 标签的点击事件
void CardController::handleLabelClick() {
    undo(); // 撤销
}