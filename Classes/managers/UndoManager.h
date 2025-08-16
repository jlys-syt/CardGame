#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include "../models/UndoModel.h"

/**
* @class UndoManager
* @notos UndoManager 的管理类
* @duty 提供 UndoModel 模型的操作接口
* @scene 对 UndoModel 内部的回退栈进行修改，和元素个数判断
*/

class UndoManager {
public:

    UndoManager(UndoModel& undoModel) {
        _undoModel = undoModel;
    }
    
    void recordState(const UndoCardPosition& state) { // 添加回退状态
        _undoModel.addUndo(state);
    }
    
    bool undo(UndoCardPosition& outState) { // 删除回退状态，并记录在 outState 中进行返回
        return _undoModel.undo(outState);
    }
    
    bool canUndo() const { // 判断能否回退
        return _undoModel.UndoStackNEmpty();
    }

    void clearStates() { // 清空回退栈
        _undoModel.clearStack();
    }

    int getUndoSize() { // 获得回退栈卡牌状态的个数
        return _undoModel.getSize();
    }

private:
    UndoModel _undoModel;
};
#endif