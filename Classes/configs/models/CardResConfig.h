#pragma once
#ifndef CARDRESCONFIG_H
#define CARDRESCONFIG_H
#include <string>
#include <array>
#include "LevelConfig.h"

/**
* @class CardResConfig
* @notos ��̬�࣬���ݼ��صĿ�Ƭģ�͵�����ֵ�����Ӧ��Դ�ĵ�ַ
* @duty ������Դ��ַ
* @scene ������Ϸ��Դ
*/

class CardResConfig {
public:
    // ��ȡ����ͼƬ��ַ
    static std::string getBackGroundSrc() {
        return "res/card_general.png";
    }

    // ��ȡ��Ƭ��ɫ��ַ
    static std::string getSuitSrc(CardSuitType suit) {
        switch (suit) {
        case CardSuitType::CST_CLUBS:    return "res/suits/club.png";
        case CardSuitType::CST_DIAMONDS: return "res/suits/diamond.png";
        case CardSuitType::CST_HEARTS:   return "res/suits/heart.png";
        case CardSuitType::CST_SPADES:   return "res/suits/spade.png";
        default: return ""; // ����Ƿ�ö��
        }
    }

    // ���С���ֵ�ַ
    static std::string getSmallNumberSrc(CardSuitType suit, CardFaceType face) {
        std::string colorStr = suitToColor(suit);
        std::string faceStr = faceToString(face);
        if (colorStr.empty() || faceStr.empty()) {
            return "";
        }
        return "res/number/small_" + colorStr + "_" + faceStr + ".png";
    }

    //��ô����ֵ�ַ
    static std::string getBigNumberSrc(CardSuitType suit, CardFaceType face) {
        std::string colorStr = suitToColor(suit);
        std::string faceStr = faceToString(face);
        if (colorStr.empty() || faceStr.empty()) {
            return "";
        }
        return "res/number/big_" + colorStr + "_" + faceStr + ".png";
    }

private:
    static std::string faceToString(CardFaceType face) { // ��ö��ֵתΪ������ֵ�ַ� 
        int index = static_cast<int>(face);
        // У���Ƿ���ö�ٷ�Χ
        if (index < 0 || index >= static_cast<int>(CardFaceType::CFT_NUM_CARD_FACE_TYPES)) {
            return ""; 
        }

        const std::string faceStrs[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
        return faceStrs[index];
    }

    static std::string suitToColor(CardSuitType suit) { // ���ݻ�ɫ���ؽ����ֵĿ�����ɫ���Ա����·����ַ
        if (suit == CardSuitType::CST_CLUBS || suit == CardSuitType::CST_SPADES) {
            return "black";
        }
        else {
            return "red";
        }
    }
};

#endif