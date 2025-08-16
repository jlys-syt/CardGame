#include "CardController.h"

 // ͨ����Ϸģ�ͽ��й����ʼ��
CardController::CardController(GameModel gameModel)
    : _gameModel(gameModel), _undoManager(gameModel.getUndoModel()) {}

CardController::~CardController() {}

 // ���濨��ƥ�䣬ƥ��ɹ�����¼״̬���������¼�
void CardController::clickPlayFieldCard(CardModel& card)
{
    CCLOG(u8"playerfield�ƶѴ���");
    if (_undoManager.getUndoSize() == 0) // ������
    {
        CCLOG(u8"������");
        return;
    }

    int face1 = static_cast<int>(card.getFaceType());
    // ������ƶ�����face
    int face2 = static_cast<int>(getHandCard().getFaceType());
    if (abs(face1 - face2) == 1) { // ���һ��ƥ��ɹ�
        UndoCardPosition state;
        state.cardId = card.getCardId(); // ����ջ��¼��״̬
        state.position = card.getPosition();
        state.zone = card.getZone();
        _undoManager.recordState(state);
        moveToHandPos(card);
    }
}

 // ������ƣ����������Ϣ������ move to ����λ��
void CardController::clickStackCard(CardModel& card) {
    UndoCardPosition state;
    state.cardId= card.getCardId();
    state.position = card.getPosition();
    state.zone = card.getZone();
    _undoManager.recordState(state);
    CardManager* cardManager = getCardManager(card);
    CCLOG(u8"stack�ƶѴ���");
    moveToHandPos(card);
}

 // ��ȡ����һ������ģ��
CardModel CardController::getHandCard() {
    UndoCardPosition state;
    if (_undoManager.undo(state)) {
        _undoManager.recordState(state); // state���޸�Ϊ����ջ��ջ������״̬
        auto& playfield = _gameModel.getPlayfield(); // ���� state.cardId ��ȡ CardModel ģ��
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
    return CardModel(cocos2d::Vec2::ZERO, CardSuitType::CST_SPADES, CardFaceType::CFT_ACE); // �쳣����
}

 // �ص���λ��
void CardController::moveToOldPos(const UndoCardPosition& state) {
    auto& playField = _gameModel.getPlayfield();
    auto& stackField = _gameModel.getStackfield();

    for (auto card : playField) {
        if (card.getCardId() == state.cardId) { // �鿴�Ƿ�����������
            CardView* cardView = getCardView(card);
            if (cardView) {
                auto moveTo = cocos2d::MoveTo::create(0.5f, state.position);
                cardView->runAction(moveTo); // move����λ��
                card.setPosition(state.position); // �޸Ŀ���ģ�͵�λ�á�������Ϣ
                card.setZone(state.zone);
                cardView->setGlobalZOrder(0);
            }
            return;
        }
    }

    for (auto card : stackField) { // �鿴�Ƿ��ڶ������޸Ŀ���ģ�͵�λ�á�������Ϣ�� move ����Ӧλ��
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

 // ��ÿ��ƵĹ������
CardManager* CardController::getCardManager(const CardModel& card) {
    CardManager* manager = CardIdManagerMap::getInstance().getCardManager(card.getCardId());
    return manager;
}

 // ǰ������δ���������£���� CardView �� CardManager ��ѭ��������������⣬�� CardIdManagerMap ʵ��ֱ�ӻ�ÿ�����ͼ
CardView* CardController::getCardView(const CardModel& card)
{
    CardView* view = CardIdManagerMap::getInstance().getCardView(card.getCardId()); 
    return view;
}

 // �����Ƶ���߼�
void CardController::moveToHandPos(CardModel& card) {
    if (card.getZone() != CardZone::Hand) { // �������Լ�ƥ��
        auto oldZone = card.getZone();
        cocos2d::Vec2 newPos(450, 160);
        CardView* cardView = getCardView(card); // ��ÿ�����ͼ������������Ϣ
        card.setZone(CardZone::Hand);
        card.setPosition(newPos);
        if (cardView) {
            CCLOG(u8"�ƶ����ƣ�id: %d, %d -> %d", card.getCardId(),oldZone,card.getZone());
            auto moveTo = cocos2d::MoveTo::create(0.5f, newPos); // �ƶ�����������
            cardView->runAction(moveTo);
            if (_undoManager.getUndoSize() != 0) {
                CardModel& lastCard = getHandCard();
                cardView->setLocalZOrder(getCardView(lastCard)->getLocalZOrder() + 1); // �㼶�����Ƶ�������һ�Ŵ�
            }
        }
    }
}

 // ���� backLabel ��ǩ�ĵ���¼�
void CardController::handleLabelClick() {
    UndoCardPosition state;
    if (_undoManager.undo(state)) { // state�޸�Ϊջ��״̬��Ϣ
        moveToOldPos(state);
    }
    CCLOG(u8"�޻���״̬");
}
