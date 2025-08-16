#pragma once
#ifndef LEVELCONFIGLOADER_H
#define LEVELCONFIGLOADER_H

#include "json/rapidjson.h"
#include "json/document.h"
#include "../models/LevelConfig.h"
#include <string>

/**
* @class LevelConfigLoader
* @notos 加载配置类，设置为静态类
* @duty 解析json字符串，将配置项存入类LevelConfig
* @scene 结合rapidjson库解析文件，将字符串进行反序列化
*/

class LevelConfigLoader final { // fianl 不能被继承
public:
	static LevelConfig* loadLevelConfig(std::string fileName); // 根据fileName，加载配置文件
private:
	static int uniqueId; // 用于指定CardModel的唯一性id
	static bool parseToCardModel(rapidjson::Value& cardInfo, std::vector<CardModel>& cards, CardZone zone); // 构造CardModel模型，并存储在LevelConfig中的相应容器

	// 静态类
	LevelConfigLoader() = default;
	LevelConfigLoader(const LevelConfigLoader&) = delete;
	LevelConfigLoader& operator=(const LevelConfigLoader&) = delete;
};

#endif