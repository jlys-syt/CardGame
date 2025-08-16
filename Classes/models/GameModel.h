#pragma once
#ifndef GAMEMODEL_H_
#define GAMEMODEL_H_

#include "../models/CardModel.h"
#include "../configs/models/LevelConfig.h"
#include "../models/UndoModel.h"

/**
* @class GameModel
* @notos ��Ϸģ����
* @duty ��������ʱ�� ���ƿ�Ƭģ�͡����ƿ���ģ�͡��Լ�����ջ��ʵ�ֶ���
* @scene ����ʱ�������壬���Խ��мӹ�
*/

class GameModel {
public:
    GameModel(LevelConfig* config) { // ����̬����ת��Ϊ����ʱ��Ϸ����
        if (config) {
            // ��ʼ����Ϸ����������������
            _playfield = config->getPlayfield();
            // ��ʼ������������������
            _stackfield = config->getStack();
            // ��ʼ������ջ
            _undoModel.clearStack();
        }
    }
    // ��ȡ playfield ����Ŀ�Ƭģ��
    const std::vector<CardModel>& getPlayfield() const {
        return _playfield;
    }
    // ��ȡ stackfield ����Ŀ�Ƭģ��
    const std::vector<CardModel>& getStackfield() const {
        return _stackfield;
    }
    // ��ȡ UndoModel ����
    UndoModel& getUndoModel() {
        return _undoModel;
    }
    // �� playfield ���
    void addCardToPlayfield(const CardModel& card) {
        _playfield.push_back(card);
    }
    // �� stackfield ���
    void addCardToStackfield(const CardModel& card) {
        _stackfield.push_back(card);
    }
    // �� playfield ɾ��һ�ſ�Ƭ
    void removeCardFromPlayfield(int id) {
        for (auto it = _playfield.begin(); it != _playfield.end(); ++it) {
            if (it->getCardId() == id) {
                _playfield.erase(it);
                break;
            }
        }
    }
    // �� stackfield �Ƴ�һ�ſ�Ƭ
    void removeCardFromStackfield(int id) {
        for (auto it = _stackfield.begin(); it != _stackfield.end(); ++it) {
            if (it->getCardId() == id) {
                _stackfield.erase(it);
                break;
            }
        }
    }
private:
    std::vector<CardModel> _playfield; // �洢���ƶ�����Ŀ��ƶ���
    std::vector<CardModel> _stackfield; // �洢�����ƶ�����Ŀ��ƶ���
    UndoModel _undoModel; // �洢�Ѿ������Ŀ��ƶ���
};

#endif