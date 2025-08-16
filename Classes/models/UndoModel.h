#pragma once
#ifndef UNDOMODEL_H
#define UNDOMODEL_H

#include "cocos2d.h"
#include "../models/CardModel.h"
#include <stack>

// 记录需要回退的位置信息
struct UndoCardPosition
{
    int cardId;
    Vec2 position;
    CardZone zone;
};

/**
* @class UndoModel
* @notos 回退模型类
* @duty 存储回退的卡片信息，提供操作方法
* @scene 为 UndoManager 提供底层数据接口和操作接口
*/

class UndoModel {
public:
    UndoModel() = default;
    void addUndo(const UndoCardPosition& topPos) {
        _undoStack.push(topPos);  // 
    }

    // 回退炒作，pop 栈顶记录
    bool UndoModel::undo(UndoCardPosition& topPos) { //返回值通过参数topPos带回
        if (_undoStack.empty()) { // 无记录
            return false;
        }
        // 取出最后一次操作的卡片位置信息
        topPos = _undoStack.top();
        // 删除记录
        _undoStack.pop();
        return true;
    }

    //清除保存的回退记录
    void UndoModel::clearStack() {
        while (!_undoStack.empty())
        {
            _undoStack.pop();
        }
    }

    bool UodoStackIsNEmpty() const { return !_undoStack.empty(); } // 判断回退栈是否为空

    int getSize() const { return _undoStack.size(); } // 返回回退栈的的记录个数
private:
    std::stack<UndoCardPosition> _undoStack; // 通过栈保存可回退卡片记录
};

#endif