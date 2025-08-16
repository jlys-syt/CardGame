#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include "../models/CardModel.h"
#include "cocos2d.h"

class CardView; // 前向声明

/**
* @class CardManager
* @notos 持有视图指针和对应的卡片模型
* @duty 提供视图指针、卡片模型的获取接口，配置 view 的 touch 事件
* @scene 持有视图、卡片模型的一方，可以通过本类获取另一方
*/

class CardManager {
public:
    CardManager(const CardModel& model);
    ~CardManager();

    // 向模型的 id 和 管理器的映射 map 表中进行注册，视图指针和数据模型的初始化
    void setCard(const CardModel& model, CardView* view);
    void setupTouchEvents(); // 绑定 touch 事件

    // 相应的绑定事件
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

    // 设置点击回调函数
    void setCardClickedCallback(const std::function<void()>& callback);
    CardView* getView() { return _view; }
    CardModel getModel() { return _model; }

private:
    CardModel _model;
    CardView* _view;
    bool _isSelected;

    std::function<void()> _cardClickedCallback;
};

#endif