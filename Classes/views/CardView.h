#ifndef CARDVIEW_H
#define CARDVIEW_H

#include "cocos2d.h"
#include "../models/CardModel.h"
#include "../configs/models/CardResConfig.h"
#include "../managers/CardManager.h"

USING_NS_CC;

class CardModel; // 前向声明

/**
* @class CardView
* @notos 静态类，卡片视图
* @duty 加载卡片视图的图片资源，
* @scene 渲染卡片界面
*/

class CardView : public Node {
public:
    using ClickCallback = std::function<void(CardView* cardView)>;

    static CardView* create(const CardModel& model, const Vec2& offset); // 创建的对象，由内存池进行释放    

    bool init(const CardModel& model, const Vec2& offset); // 设置视图的位置， 生成CardManager对象，并初始化CardManager的视图指针和数据模型
    bool loadBackground(); // 加载背景资源
    bool loadSmallNumber(const CardModel& model); // 加载小数字
    bool loadBigNumber(const CardModel& model); // 加载大数字
    bool loadSuitIcon(const CardModel& model); // 加载花色图标
    
    void setClickCallback(const ClickCallback& callback); // 设置回调

    bool containsPoint(const cocos2d::Vec2& point); // 判断点是否在当前卡牌视图中

    CardManager* _cardManager; //

private:
    Sprite* _background = nullptr;  // 卡片背景
    Sprite* _smallNumber = nullptr; // 左上小数字
    Sprite* _bigNumber = nullptr;   // 中间大数字
    Sprite* _suitIcon = nullptr;    // 右上花色

    // 指定资源偏移向量，可以后序统一更改
    const Vec2 kSmallNumberPos = Vec2(-45, 80);  // 左上小数字
    const Vec2 kSuitIconPos = Vec2(45, 80);     // 右上花色
    const Vec2 KBigNumberPos = Vec2(0, 0);       // 中间大数字

    ClickCallback _clickCallback;
    bool _isSelected;
};

#endif