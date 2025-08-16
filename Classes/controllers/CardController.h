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
    void clickPlayFieldCard(CardModel& card);

    // ���Stack���Ŀ��ƣ���¼��״̬��UndoModel��
    void clickStackCard(CardModel& card);

    // ������˱�ǩ����¼�
    void handleLabelClick();    

private:
    GameModel _gameModel;
    UndoManager _undoManager;

    // ��ȡ����
    CardModel getHandCard();

    //�ƶ�����������
    void moveToHandPos(CardModel& card);

    // �ƶ����Ƶ�ԭλ��
    void moveToOldPos(const UndoCardPosition& state);

    // ����CardModel��ȡCardManager
    CardManager* getCardManager(const CardModel& card);

    // ����CardModel��ȡ��Ӧ����ͼ
    CardView* getCardView(const CardModel& card);
};
#endif