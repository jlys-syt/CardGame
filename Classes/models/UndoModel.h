#pragma once
#ifndef UNDOMODEL_H
#define UNDOMODEL_H

#include "cocos2d.h"
#include "../models/CardModel.h"
#include <stack>

// ��¼��Ҫ���˵�λ����Ϣ
struct UndoCardPosition
{
    int cardId;
    Vec2 position;
    CardZone zone;
};

/**
* @class UndoModel
* @notos ����ģ����
* @duty �洢���˵Ŀ�Ƭ��Ϣ���ṩ��������
* @scene Ϊ UndoManager �ṩ�ײ����ݽӿںͲ����ӿ�
*/

class UndoModel {
public:
    UndoModel() = default;
    void addUndo(const UndoCardPosition& topPos) {
        _undoStack.push(topPos);  // 
    }

    // ���˲�����pop ջ����¼
    bool UndoModel::undo(UndoCardPosition& topPos) { //����ֵͨ������topPos����
        if (_undoStack.empty()) { // �޼�¼
            return false;
        }
        // ȡ�����һ�β����Ŀ�Ƭλ����Ϣ
        topPos = _undoStack.top();
        // ɾ����¼
        _undoStack.pop();
        return true;
    }

    //�������Ļ��˼�¼
    void UndoModel::clearStack() {
        while (!_undoStack.empty())
        {
            _undoStack.pop();
        }
    }

    bool UndoStackNEmpty() const { return !_undoStack.empty(); } // �жϻ���ջ�Ƿ�Ϊ��

    int getSize() const { return _undoStack.size(); } // ���ػ���ջ�ĵļ�¼����
private:
    std::stack<UndoCardPosition> _undoStack; // ͨ��ջ����ɻ��˿�Ƭ��¼
};

#endif