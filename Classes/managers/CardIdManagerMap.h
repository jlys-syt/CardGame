#pragma once
#ifndef CARDIDVIEWMAP_H
#define CARDIDVIEWMAP_H

#include "CardManager.h"
#include <unordered_map>
#include "CardView.h"

class CardIdManagerMap {
public:
    static CardIdManagerMap& getInstance() {
        static CardIdManagerMap instance;
        return instance;
    }

    void addCardManager(int cardId, CardManager* manager) {
        _cardIdManagerMap[cardId] = manager;
    }

    CardManager* getCardManager(int cardId) {
        auto it = _cardIdManagerMap.find(cardId);
        if (it != _cardIdManagerMap.end()) {
            return it->second;
        }
        return nullptr;
    }

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