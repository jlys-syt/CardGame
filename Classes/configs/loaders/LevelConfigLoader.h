#pragma once
#ifndef LEVELCONFIGLOADER_H
#define LEVELCONFIGLOADER_H

#include "json/rapidjson.h"
#include "json/document.h"
#include "../models/LevelConfig.h"
#include <string>

/**
* @class LevelConfigLoader
* @notos ���������࣬����Ϊ��̬��
* @duty ����json�ַ������������������LevelConfig
* @scene ���rapidjson������ļ������ַ������з����л�
*/

class LevelConfigLoader final { // fianl ���ܱ��̳�
public:
	static LevelConfig* loadLevelConfig(std::string fileName); // ����fileName�����������ļ�
private:
	static int uniqueId; // ����ָ��CardModel��Ψһ��id
	static bool parseToCardModel(rapidjson::Value& cardInfo, std::vector<CardModel>& cards, CardZone zone); // ����CardModelģ�ͣ����洢��LevelConfig�е���Ӧ����

	// ��̬��
	LevelConfigLoader() = default;
	LevelConfigLoader(const LevelConfigLoader&) = delete;
	LevelConfigLoader& operator=(const LevelConfigLoader&) = delete;
};

#endif