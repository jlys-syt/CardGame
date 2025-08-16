#pragma once
#ifndef CARDIDVIEWMAP_H
#define CARDIDVIEWMAP_H

#include "../managers/CardManager.h"
#include <unordered_map>
#include "../views/CardView.h"

/**
* @class CardIdManagerMap
* @notos 卡片唯一 id 属性和对应 CardManager 对象的映射，采用单例模式
* @duty 记录卡片唯一 id 属性和对应 CardManager 对象的映射关系，可以进行注册，以及提供获得管理和视图的接口
* @scene 获得 CardManager 、视图对象
*/

class CardIdManagerMap {
public:
    static CardIdManagerMap& getInstance() {
        static CardIdManagerMap instance;
        return instance;
    }

    // 注册映射关系
    void addCardManager(int cardId, CardManager* manager) {
        _cardIdManagerMap[cardId] = manager;
    }

    // 根据卡片 id 获得对应的卡片管理对象
    CardManager* getCardManager(int cardId) {
        auto it = _cardIdManagerMap.find(cardId);
        if (it != _cardIdManagerMap.end()) {
            return it->second;
        }
        return nullptr;
    }

    // 根据卡片 id 获得对应的卡片视图对象
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