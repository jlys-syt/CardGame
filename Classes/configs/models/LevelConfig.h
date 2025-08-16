#pragma once
#ifndef CONFIGSMODELSLEVELCONFIG_H
#define CONFIGSMODELSLEVELCONFIG_H

#include <vector>
#include "../../models/CardModel.h"

/**
* @class LevelConfig
* @notos 存储加载配置文件，提取的静态数据
* @duty 存储静态数据，提供获取接口
* @scene 加载游戏数据
*/

class LevelConfig final {
public:
    std::vector<CardModel> getPlayfield() {
        return _playfieldCards;
    }

    std::vector<CardModel> getStack() {
        return _stackCards;
    }

private:
	std::vector<CardModel> _playfieldCards; // 桌面区域卡牌模型
	std::vector<CardModel> _stackCards; // 堆区卡牌模型

    LevelConfig() = default;
    ~LevelConfig() = default;
    LevelConfig(const LevelConfig&) = delete;
    LevelConfig& operator=(const LevelConfig&) = delete;

    friend class LevelConfigLoader;
};

#endif