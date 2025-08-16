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
* @notos ��̬��,��Ϸ��ͼ
* @duty ��ʼ��������Ŀ�Ƭģ����ͼ��ע��backLabel�ĵ���¼�,���ÿ�Ƭģ�͵ĵ���߼��Ļص�����
* @scene ���عؿ���Ϸ���ݣ���������ʱ��Ϸ����
*/

class GameView : public cocos2d::Node {
public:
	static GameView* create(GameModel& model); // ͨ�� GameModel ģ�ͽ��г�ʼ��
private:
	void generateCardViews(GameModel& model); // ���ɿ�Ƭ��ͼ��ͼ������ʼ��
	bool init(GameModel& model); // ���û��˱�ǩ���ı����ݣ���λ����Ϣ
	void registerTouchEvent(); // ע��backLabel��ǩ�Ĵ����¼�
	void onClickedLabel(); // �����Ĵ�����

	std::vector<CardView*> _playfieldCardViews; // �洢 playfield �����еĿ�Ƭ��ͼ
	std::vector<CardView*> _stackfieldCardViews; // �洢 stackfield �����еĿ�Ƭ��ͼ
	cocos2d::Label* _backLabel; // ���˱�ǩ
	CardController* _cardController; // ��Ƭ����������װ�˿�Ƭ�Ĵ�����
};

#endif