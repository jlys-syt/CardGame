#pragma once
#ifndef GAMEMODELFROMLEVELGENERATOR_H
#define GAMEMODELFROMLEVELGENERATOR_H

#include "../models/GameModel.h"
#include <string>
#include "../configs/loaders/LevelConfigLoader.h"
#include "../views/GameView.h"

/**
* @class GameModelFromLevelGenerator
* @notos ��̬��
* @duty �ṩ������Ϸģ�� �� ������Ϸ��ͼ����Ľӿ�
* @scene ���عؿ���Ϸ���ݡ���Ⱦ����
*/

class GameModelFromLevelGenerator
{
public:
    // ���ü����������ӿڣ���ȡ��̬���ݣ��ٽ���̬���ݼӹ�Ϊ����ʱ��Ϸ����(���� GameModel)
    static GameModel generateGameModel(const std::string configFileName) {
        auto config = LevelConfigLoader::loadLevelConfig(configFileName);
        GameModel gameModel(config);
        return gameModel;
    }

    static void generateGameView(GameModel& gameModel, Node* parent) {
        // ���� GameView ʵ��
        auto gameView = GameView::create(gameModel);
        if (gameView) {
            parent->addChild(gameView, 1);
        }
    }
private:
	// ��̬��
    GameModelFromLevelGenerator() = default;
    GameModelFromLevelGenerator(const GameModelFromLevelGenerator&) = delete;
    GameModelFromLevelGenerator& operator=(const GameModelFromLevelGenerator&) = delete;
};

#endif