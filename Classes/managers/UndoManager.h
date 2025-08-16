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
    
    void recordUndoState(const UndoCardPosition& state) { // 添加回退记录
        _undoModel.addUndo(state);
    }
    
    bool undo(UndoCardPosition& outState) { // 删除回退记录，并记录在 outState 中进行返回
        return _undoModel.undo(outState);
    }
    
    bool canUndo() const { // 判断能否回退
        return _undoModel.UodoStackIsNEmpty();
    }

    void clearUndoHistory() { // 清空回退栈
        _undoModel.clearStack();
    }

    int getUndoSize() { // 获得回退栈卡牌记录的个数
        return _undoModel.getSize();
    }

private:
    UndoModel _undoModel;
};
#endif