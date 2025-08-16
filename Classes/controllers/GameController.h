#pragma once
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <string>
#include "../configs/loaders/LevelConfigLoader.h"
#include "../views/GameView.h"
#include "../services/GameModelFromLevelGenerator.h"

/**
* @class GameController
* @notos 游戏关卡初始化入口，采用单例模式
* @duty 根据关卡配置文件目录进行解析
*/

class GameController
{
public:
	static GameController& getIntance()
	{
		static GameController gameController;
		return gameController;
	}

	// 游戏启动入口
	void startGame(const std::string& configFileName, Node* parent)
	{
		// 加载配置文件, 进行一系列的初始化，绑定事件和传递回调函数构筑视图
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