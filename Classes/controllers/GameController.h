#pragma once
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <string>
#include "../configs/loaders/LevelConfigLoader.h"
#include "../views/GameView.h"
#include "../services/GameModelFromLevelGenerator.h"

/**
* @class GameController
* @notos ��Ϸ�ؿ���ʼ����ڣ����õ���ģʽ
* @duty ���ݹؿ������ļ�Ŀ¼���н���
*/

class GameController
{
public:
	static GameController& getIntance()
	{
		static GameController gameController;
		return gameController;
	}

	// ��Ϸ�������
	void startGame(const std::string& configFileName, Node* parent)
	{
		// ���������ļ�, ����һϵ�еĳ�ʼ�������¼��ʹ��ݻص�����������ͼ
		auto gameModel = GameModelFromLevelGenerator::generateGameModel(configFileName);
		GameModelFromLevelGenerator::generateGameView(gameModel, parent);
	}
private:
	GameController() = default;
	~GameController() = default;
	GameController(const GameController&) = delete;
	GameController& operator=(const GameController&) = delete;
};


#endif