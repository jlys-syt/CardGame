#ifndef CARDMODEL_H
#define CARDMODEL_H

#include "cocos2d.h"
USING_NS_CC;

/**
* @class CardModel
* @notos 卡片实体类
* @duty 抽象出来卡片实体类，并提供的 get 和 set 方法
* @scene 数据可以加工成 CardModel 对象类型进行存储
*/

enum class CardZone {
    Playfield,  // 主牌区
    Stack,      // 备用牌堆
    Hand,
    Unknown     // 兜底值，避免非法状态
};

enum class CardSuitType {
    CST_NONE = -1,
    CST_CLUBS,      // 梅花
    CST_DIAMONDS,   // 方块
    CST_HEARTS,     // 红桃
    CST_SPADES,     // 黑桃
    CST_NUM_CARD_SUIT_TYPES
};


enum class CardFaceType {
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

class CardModel {
public:
    CardModel(Vec2 position = Vec2::ZERO, CardSuitType suitType = CardSuitType::CST_CLUBS,
        CardFaceType faceType = CardFaceType::CFT_ACE)
        : _cardId(-1)
        , _zone(CardZone::Unknown)
        , _position(position)
        , _suitType(suitType)
        , _faceType(faceType)
    {}
    CardModel(int cardId, CardZone zone, Vec2 position, CardSuitType suitType, CardFaceType faceType)
        : _cardId(cardId)
        , _zone(zone)
        , _position(position)
        , _suitType(suitType)
        , _faceType(faceType)
    {}
    // 属性的 get 方法
    const int getCardId() const { return _cardId; }
    const CardZone getZone() const { return _zone; }
    const cocos2d::Vec2& getPosition() const { return _position; }
    CardSuitType getSuitType() const { return _suitType; }
    CardFaceType getFaceType() const { return _faceType; }

    // 属性的 set 方法
    void setCardId(int cardId) { _cardId = cardId; }
    void setZone(CardZone zone) { _zone = zone; }
    void setPosition(Vec2 position) { _position = position; }
    void setSuitType(CardSuitType suitType) { _suitType = suitType; }
    void setCardFaceType(CardFaceType faceType) { _faceType = faceType; }
private:
    int _cardId; //卡片唯一标识位，-1表示未初始化
    CardZone _zone; // 区域
    Vec2 _position; // 位置
    CardSuitType _suitType; // 花色
    CardFaceType _faceType; // 面值大小
};

#endif