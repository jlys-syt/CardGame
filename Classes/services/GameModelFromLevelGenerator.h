#pragma once
#ifndef GAMEMODELFROMLEVELGENERATOR_H
#define GAMEMODELFROMLEVELGENERATOR_H

#include "../models/GameModel.h"
#include <string>
#include "../configs/loaders/LevelConfigLoader.h"
#include "../views/GameView.h"

/**
* @class GameModelFromLevelGenerator
* @notos 静态类
* @duty 提供生成游戏模型 和 获得游戏视图对象的接口
* @scene 加载关卡游戏数据、生成运行时游戏数据
*/

class GameModelFromLevelGenerator
{
public:
    // 调用加载配置器接口，提取静态数据，再将静态数据加工为运行时游戏数据(构筑 GameModel)
    static GameModel generateGameModel(const std::string configFileName) {
        auto config = LevelConfigLoader::loadLevelConfig(configFileName);
        GameModel gameModel(config);
        return gameModel;
    }

    static void generateGameView(GameModel& gameModel, Node* parent) {
        // 创建 GameView 实例
        auto gameView = GameView::create(gameModel);
        if (gameView) {
            parent->addChild(gameView, 1);
        }
    }
private:
	// 静态类
    GameModelFromLevelGenerator() = default;
    GameModelFromLevelGenerator(const GameModelFromLevelGenerator&) = delete;
    GameModelFromLevelGenerator& operator=(const GameModelFromLevelGenerator&) = delete;
};

#endif