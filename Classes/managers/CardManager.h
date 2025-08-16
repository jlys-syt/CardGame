#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include "../models/CardModel.h"
#include "cocos2d.h"

class CardView; // ǰ������

/**
* @class CardManager
* @notos ������ͼָ��Ͷ�Ӧ�Ŀ�Ƭģ��
* @duty �ṩ��ͼָ�롢��Ƭģ�͵Ļ�ȡ�ӿڣ����� view �� touch �¼�
* @scene ������ͼ����Ƭģ�͵�һ��������ͨ�������ȡ��һ��
*/

class CardManager {
public:
    CardManager(const CardModel& model);
    ~CardManager();

    // ��ģ�͵� id �� ��������ӳ�� map ���н���ע�ᣬ��ͼָ�������ģ�͵ĳ�ʼ��
    void setCard(const CardModel& model, CardView* view);
    void setTouchEvents(); // �� touch �¼�

    // ��Ӧ���¼�
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

    // ���õ���ص�����
    void setCardClickedCallback(const std::function<void()>& callback);
    CardView* getView() { return _view; }
    CardModel getModel() { return _model; }

private:
    CardModel _model;
    CardView* _view;
    std::function<void()> _cardClickedCallback;
};

#endif