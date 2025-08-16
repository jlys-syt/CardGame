#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include "../models/UndoModel.h"

/**
* @class UndoManager
* @notos UndoManager �Ĺ�����
* @duty �ṩ UndoModel ģ�͵Ĳ����ӿ�
* @scene �� UndoModel �ڲ��Ļ���ջ�����޸ģ���Ԫ�ظ����ж�
*/

class UndoManager {
public:

    UndoManager(UndoModel& undoModel) {
        _undoModel = undoModel;
    }
    
    void recordState(const UndoCardPosition& state) { // ��ӻ���״̬
        _undoModel.addUndo(state);
    }
    
    bool undo(UndoCardPosition& outState) { // ɾ������״̬������¼�� outState �н��з���
        return _undoModel.undo(outState);
    }
    
    bool canUndo() const { // �ж��ܷ����
        return _undoModel.UndoStackNEmpty();
    }

    void clearStates() { // ��ջ���ջ
        _undoModel.clearStack();
    }

    int getUndoSize() { // ��û���ջ����״̬�ĸ���
        return _undoModel.getSize();
    }

private:
    UndoModel _undoModel;
};
#endif