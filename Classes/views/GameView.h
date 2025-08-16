#pragma once
#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "2d/CCNode.h"
#include "../models/GameModel.h"
#include "../controllers/CardController.h"
#include "CardView.h"
#include <vector>

/**
* @class GameView
* @notos 静态类,游戏视图
* @duty 初始化各区域的卡片模型视图，注册backLabel的点击事件,设置卡片模型的点击逻辑的回调函数
* @scene 渲染界面
*/

class GameView : public cocos2d::Node {
public:
	static GameView* create(GameModel& model); // 通过 GameModel 模型进行初始化
private:
	void generateCardViews(GameModel& model); // 生成卡片视图视图，并初始化
	bool init(GameModel& model); // 设置回退标签的文本内容，和位置信息
	void registerTouchEvent(); // 注册backLabel标签的触摸事件
	void onClickedLabel(); // 点击后的处理函数

	std::vector<CardView*> _playfieldCardViews; // 存储 playfield 区域中的卡片视图
	std::vector<CardView*> _stackfieldCardViews; // 存储 stackfield 区域中的卡片视图
	cocos2d::Label* _backLabel; // 回退标签
	CardController* _cardController; // 卡片控制器，封装了卡片的处理函数
};

#endif