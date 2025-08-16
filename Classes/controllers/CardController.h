#ifndef CARDCONTROLLER_H
#define CARDCONTROLLER_H

#include "../models/GameModel.h"
#include "../managers/UndoManager.h"
#include "../services/CardIdManagerMap.h"
#include "../views/CardView.h"
#include <functional>
#include <vector>

/**
* @class CardController
* @notos ��װ�˶Կ��Ƶ�ƥ�䡢��������˵Ĺ����߼�ʵ��
* @duty �ṩ�������߼��Ľӿ�
* @scene ��������ͼ����¼��ĺ����߼�
*/

class CardController {
public:
    CardController(GameModel gameModel);
    ~CardController();

    // ������ƶ��е��ƺ͵���ƥ��
    bool selectCardFromPlayefieldAndMatch(CardModel& selectedCard);

    // ���Stack���Ŀ��ƣ���¼��״̬��UndoModel��
    void clickStackCard(CardModel& card);

    // ����Ƭ����¼�
    void handleCardClicked(CardModel& card);

    // ������˰�ť
    bool undo();

    // ������˱�ǩ����¼�
    void handleLabelClick();
private:
    GameModel _gameModel;
    UndoManager _undoManager;

    // ��ȡ���Ƶ�CardModel
    CardModel getBottomCard();

    // ����������Ƿ�ƥ�䣬���� bool ����
    bool isCardMatch(const CardModel& card1, const CardModel& card2);

    // �ƶ����Ƶ�ԭλ��
    void moveToOldPos(const UndoCardPosition& state);

    // ����CardModel��ȡCardManager
    CardManager* getCardManager(const CardModel& card);

    // ����CardModel��ȡ��Ӧ����ͼ
    CardView* getCardView(const CardModel& card);
};
#endif