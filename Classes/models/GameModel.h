#pragma once
#ifndef GAMEMODEL_H_
#define GAMEMODEL_H_

#include "../models/CardModel.h"
#include "../configs/models/LevelConfig.h"
#include "../models/UndoModel.h"

/**
* @class GameModel
* @notos 游戏模型类
* @duty 储存运行时的 堆牌卡片模型、桌牌卡面模型、以及回退栈的实现对象
* @scene 运行时数据载体，可以进行加工
*/

class GameModel {
public:
    GameModel(LevelConfig* config) { // 将静态数据转换为运行时游戏数据
        if (config) {
            // 初始化游戏区域容器卡牌数据
            _playfield = config->getPlayfield();
            // 初始化堆区容器卡牌数据
            _stackfield = config->getStack();
            // 初始化回退栈
            _undoModel.clearStack();
        }
    }
    // 获取 playfield 区域的卡片模型
    const std::vector<CardModel>& getPlayfield() const {
        return _playfield;
    }
    // 获取 stackfield 区域的卡片模型
    const std::vector<CardModel>& getStackfield() const {
        return _stackfield;
    }
    // 获取 UndoModel 对象
    UndoModel& getUndoModel() {
        return _undoModel;
    }
    // 向 playfield 添加
    void addCardToPlayfield(const CardModel& card) {
        _playfield.push_back(card);
    }
    // 向 stackfield 添加
    void addCardToStackfield(const CardModel& card) {
        _stackfield.push_back(card);
    }
    // 从 playfield 删除一张卡片
    void removeCardFromPlayfield(int id) {
        for (auto it = _playfield.begin(); it != _playfield.end(); ++it) {
            if (it->getCardId() == id) {
                _playfield.erase(it);
                break;
            }
        }
    }
    // 从 stackfield 移除一张卡片
    void removeCardFromStackfield(int id) {
        for (auto it = _stackfield.begin(); it != _stackfield.end(); ++it) {
            if (it->getCardId() == id) {
                _stackfield.erase(it);
                break;
            }
        }
    }
private:
    std::vector<CardModel> _playfield; // 存储主牌堆区域的卡牌对象
    std::vector<CardModel> _stackfield; // 存储备用牌堆区域的卡牌对象
    UndoModel _undoModel; // 存储已经消除的卡牌对象
};

#endif