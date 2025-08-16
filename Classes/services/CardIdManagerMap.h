#pragma once
#ifndef CARDIDVIEWMAP_H
#define CARDIDVIEWMAP_H

#include "../managers/CardManager.h"
#include <unordered_map>
#include "../views/CardView.h"

/**
* @class CardIdManagerMap
* @notos ��ƬΨһ id ���ԺͶ�Ӧ CardManager �����ӳ�䣬���õ���ģʽ
* @duty ��¼��ƬΨһ id ���ԺͶ�Ӧ CardManager �����ӳ���ϵ�����Խ���ע�ᣬ�Լ��ṩ��ù������ͼ�Ľӿ�
* @scene ��� CardManager ����ͼ����
*/

class CardIdManagerMap {
public:
    static CardIdManagerMap& getInstance() {
        static CardIdManagerMap instance;
        return instance;
    }

    // ע��ӳ���ϵ
    void addCardManager(int cardId, CardManager* manager) {
        _cardIdManagerMap[cardId] = manager;
    }

    // ���ݿ�Ƭ id ��ö�Ӧ�Ŀ�Ƭ�������
    CardManager* getCardManager(int cardId) {
        auto it = _cardIdManagerMap.find(cardId);
        if (it != _cardIdManagerMap.end()) {
            return it->second;
        }
        return nullptr;
    }

    // ���ݿ�Ƭ id ��ö�Ӧ�Ŀ�Ƭ��ͼ����
    CardView* getCardView(int cardId)
    {
        auto it = _cardIdManagerMap.find(cardId);
        if (it == _cardIdManagerMap.end())
            return nullptr;
        return _cardIdManagerMap[cardId]->getView();
    }

private:
    CardIdManagerMap() {}
    ~CardIdManagerMap() {}

    std::unordered_map<int, CardManager*> _cardIdManagerMap;
};

#endif 