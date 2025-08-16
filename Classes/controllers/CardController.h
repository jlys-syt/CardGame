#ifndef CARDCONTROLLER_H
#define CARDCONTROLLER_H

#include "../models/GameModel.h"
#include "../managers/UndoManager.h"
#include "../services/CardIdManagerMap.h"
#include "../views/CardView.h"
#include <functional>
#include <vector>

/**
* @class CardController
* @notos 封装了对卡牌的匹配、点击、回退的功能逻辑实现
* @duty 提供处理卡牌逻辑的接口
* @scene 处理卡牌视图点击事件的函数逻辑
*/

class CardController {
public:
    CardController(GameModel gameModel);
    ~CardController();

    // 点击主牌堆中的牌和底牌匹配
    void clickPlayFieldCard(CardModel& card);

    // 点击Stack区的卡牌，记录其状态到UndoModel中
    void clickStackCard(CardModel& card);

    // 处理回退标签点击事件
    void handleLabelClick();    

private:
    GameModel _gameModel;
    UndoManager _undoManager;

    // 获取手牌
    CardModel getHandCard();

    //移动到手牌区域
    void moveToHandPos(CardModel& card);

    // 移动卡牌到原位置
    void moveToOldPos(const UndoCardPosition& state);

    // 根据CardModel获取CardManager
    CardManager* getCardManager(const CardModel& card);

    // 根据CardModel获取对应的视图
    CardView* getCardView(const CardModel& card);
};
#endif