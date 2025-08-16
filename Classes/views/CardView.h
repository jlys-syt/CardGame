#ifndef CARDVIEW_H
#define CARDVIEW_H

#include "cocos2d.h"
#include "../models/CardModel.h"
#include "../configs/models/CardResConfig.h"
#include "../managers/CardManager.h"

USING_NS_CC;

class CardModel; // ǰ������

/**
* @class CardView
* @notos ��̬�࣬��Ƭ��ͼ
* @duty ���ؿ�Ƭ��ͼ��ͼƬ��Դ��
* @scene ��Ⱦ��Ƭ����
*/

class CardView : public Node {
public:
    using ClickCallback = std::function<void(CardView* cardView)>;

    static CardView* create(const CardModel& model, const Vec2& offset); // �����Ķ������ڴ�ؽ����ͷ�    

    bool init(const CardModel& model, const Vec2& offset); // ������ͼ��λ�ã� ����CardManager���󣬲���ʼ��CardManager����ͼָ�������ģ��
    bool loadBackground(); // ���ر�����Դ
    bool loadSmallNumber(const CardModel& model); // ����С����
    bool loadBigNumber(const CardModel& model); // ���ش�����
    bool loadSuitIcon(const CardModel& model); // ���ػ�ɫͼ��
    
    void setClickCallback(const ClickCallback& callback); // ���ûص�

    bool containsPoint(const cocos2d::Vec2& point); // �жϵ��Ƿ��ڵ�ǰ������ͼ��

    CardManager* _cardManager; //

private:
    Sprite* _background = nullptr;  // ��Ƭ����
    Sprite* _smallNumber = nullptr; // ����С����
    Sprite* _bigNumber = nullptr;   // �м������
    Sprite* _suitIcon = nullptr;    // ���ϻ�ɫ

    // ָ����Դƫ�����������Ժ���ͳһ����
    const Vec2 kSmallNumberPos = Vec2(-45, 80);  // ����С����
    const Vec2 kSuitIconPos = Vec2(45, 80);     // ���ϻ�ɫ
    const Vec2 KBigNumberPos = Vec2(0, 0);       // �м������

    ClickCallback _clickCallback;
    bool _isSelected;
};

#endif