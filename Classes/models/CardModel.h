#ifndef CARDMODEL_H
#define CARDMODEL_H

#include "cocos2d.h"
USING_NS_CC;

/**
* @class CardModel
* @notos ��Ƭʵ����
* @duty ���������Ƭʵ���࣬���ṩ�� get �� set ����
* @scene ���ݿ��Լӹ��� CardModel ��������
*/

enum class CardZone {
    Playfield,  // ������
    Stack,      // �����ƶ�
    Hand,
    Unknown     // ����ֵ������Ƿ�״̬
};

enum class CardSuitType {
    CST_NONE = -1,
    CST_CLUBS,      // ÷��
    CST_DIAMONDS,   // ����
    CST_HEARTS,     // ����
    CST_SPADES,     // ����
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
    // ���Ե� get ����
    const int getCardId() const { return _cardId; }
    const CardZone getZone() const { return _zone; }
    const cocos2d::Vec2& getPosition() const { return _position; }
    CardSuitType getSuitType() const { return _suitType; }
    CardFaceType getFaceType() const { return _faceType; }

    // ���Ե� set ����
    void setCardId(int cardId) { _cardId = cardId; }
    void setZone(CardZone zone) { _zone = zone; }
    void setPosition(Vec2 position) { _position = position; }
    void setSuitType(CardSuitType suitType) { _suitType = suitType; }
    void setCardFaceType(CardFaceType faceType) { _faceType = faceType; }
private:
    int _cardId; //��ƬΨһ��ʶλ��-1��ʾδ��ʼ��
    CardZone _zone; // ����
    Vec2 _position; // λ��
    CardSuitType _suitType; // ��ɫ
    CardFaceType _faceType; // ��ֵ��С
};

#endif