#pragma once
#ifndef CONFIGSMODELSLEVELCONFIG_H
#define CONFIGSMODELSLEVELCONFIG_H

#include <vector>
#include "../../models/CardModel.h"

/**
* @class LevelConfig
* @notos �洢���������ļ�����ȡ�ľ�̬����
* @duty �洢��̬���ݣ��ṩ��ȡ�ӿ�
* @scene ������Ϸ����
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
	std::vector<CardModel> _playfieldCards; // ����������ģ��
	std::vector<CardModel> _stackCards; // ��������ģ��

    LevelConfig() = default;
    ~LevelConfig() = default;
    LevelConfig(const LevelConfig&) = delete;
    LevelConfig& operator=(const LevelConfig&) = delete;

    friend class LevelConfigLoader;
};

#endif