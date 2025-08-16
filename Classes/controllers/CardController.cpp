#include "CardController.h"

 // ͨ����Ϸģ�ͽ��й����ʼ��
CardController::CardController(GameModel gameModel)
    : _gameModel(gameModel), _undoManager(gameModel.getUndoModel()) {}

CardController::~CardController() {}

 // ���濨��ƥ�䣬ƥ��ɹ�����¼״̬���������¼�
bool CardController::selectCardFromPlayefieldAndMatch(CardModel& selectedCard) {
    if (_undoManager.getUndoSize() == 0) {
        return false;
    }
    CardModel bottomCard = getBottomCard();
    CCLOG(u8"playerfield�ƶѴ���");
    if (isCardMatch(selectedCard, bottomCard)) {  // ƥ��ɹ�����¼����״̬        
        UndoCardPosition state;
        state.cardId = selectedCard.getCardId();
        state.position = selectedCard.getPosition();
        state.zone = selectedCard.getZone();
        _undoManager.recordUndoState(state);
        handleCardClicked(selectedCard); // �������¼�
        return true;
    }
    return false;
}

 // ������ƣ����������Ϣ������ move to ����λ��
void CardController::clickStackCard(CardModel& card) {
    UndoCardPosition state;
    state.cardId= card.getCardId();
    state.position = card.getPosition();
    state.zone = card.getZone();
    _undoManager.recordUndoState(state);
    CardManager* cardManager = getCardManager(card);
    CCLOG(u8"stack�ƶѴ���");
    handleCardClicked(card);
}

 // �������ƣ��˻�ԭλ��
bool CardController::undo() {
    UndoCardPosition state;
    if (_undoManager.undo(state)) { // state�޸�Ϊջ��״̬��Ϣ
        moveToOldPos(state);
        return true;
    }
    return false;
}

 // ��ȡ����ģ��,ͨ������ջ��ջ������ģ�ͻ�ȡ�����������ݽ��бȽϣ����� CardModel ģ��
CardModel CardController::getBottomCard() {
    UndoCardPosition state;
    if (_undoManager.undo(state)) {
        _undoManager.recordUndoState(state); // state���޸�Ϊ����ջ��ջ�����Ƶ�λ����Ϣ
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
    return CardModel(cocos2d::Vec2::ZERO, CardSuitType::CST_SPADES, CardFaceType::CFT_ACE); // �޻��˼�¼�����⴦��
}

 // �����Ƿ�ƥ��
bool CardController::isCardMatch(const CardModel& card1, const CardModel& card2) {
    int face1 = static_cast<int>(card1.getFaceType());
    int face2 = static_cast<int>(card2.getFaceType());
    return (face1 == face2 + 1) || (face1 == face2 - 1);
}

 // �ص���λ��
void CardController::moveToOldPos(const UndoCardPosition& state) {
    auto& playField = _gameModel.getPlayfield();
    auto& stackField = _gameModel.getStackfield();

    for (auto card : playField) { // �鿴�Ƿ������������޸Ŀ���ģ�͵�λ�á�������Ϣ�� move ����Ӧλ��
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
void CardController::handleCardClicked(CardModel& card) {
    if (card.getZone() != CardZone::Hand) { // �����������򣬻�ÿ�����ͼ���ƶ�����������
        auto oldZone = card.getZone();
        //cocos2d::Vec2 newPos(700, 400);
        cocos2d::Vec2 newPos(450, 160);
        CardView* cardView = getCardView(card);
        card.setZone(CardZone::Hand);
        card.setPosition(newPos);
        if (cardView) {
            CCLOG(u8"�ƶ����ƣ�id: %d, %d -> %d", card.getCardId(),oldZone,card.getZone());
            auto moveTo = cocos2d::MoveTo::create(0.5f, newPos);
            cardView->runAction(moveTo);
            if (_undoManager.getUndoSize() != 0) {
                CardModel& lastCard = getBottomCard();
                cardView->setLocalZOrder(getCardView(lastCard)->getLocalZOrder() + 1); // �㼶�����Ƶ�������һ�Ŵ�
            }
        }
    }
}

 // ���� backLabel ��ǩ�ĵ���¼�
void CardController::handleLabelClick() {
    undo(); // ����
}