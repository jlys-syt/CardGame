#pragma once
#ifndef CARDRESCONFIG_H
#define CARDRESCONFIG_H
#include <string>
#include <array>
#include "LevelConfig.h"

/**
* @class CardResConfig
* @notos 静态类，根据加载的卡片模型的属性值获得相应资源的地址
* @duty 返回资源地址
* @scene 加载游戏资源
*/

class CardResConfig {
public:
    // 获取背景图片地址
    static std::string getBackGroundSrc() {
        return "res/card_general.png";
    }

    // 获取卡片花色地址
    static std::string getSuitSrc(CardSuitType suit) {
        switch (suit) {
        case CardSuitType::CST_CLUBS:    return "res/suits/club.png";
        case CardSuitType::CST_DIAMONDS: return "res/suits/diamond.png";
        case CardSuitType::CST_HEARTS:   return "res/suits/heart.png";
        case CardSuitType::CST_SPADES:   return "res/suits/spade.png";
        default: return ""; // 处理非法枚举
        }
    }

    // 获得小数字地址
    static std::string getSmallNumberSrc(CardSuitType suit, CardFaceType face) {
        std::string colorStr = suitToColor(suit);
        std::string faceStr = faceToString(face);
        if (colorStr.empty() || faceStr.empty()) {
            return "";
        }
        return "res/number/small_" + colorStr + "_" + faceStr + ".png";
    }

    //获得大数字地址
    static std::string getBigNumberSrc(CardSuitType suit, CardFaceType face) {
        std::string colorStr = suitToColor(suit);
        std::string faceStr = faceToString(face);
        if (colorStr.empty() || faceStr.empty()) {
            return "";
        }
        return "res/number/big_" + colorStr + "_" + faceStr + ".png";
    }

private:
    static std::string faceToString(CardFaceType face) { // 由枚举值转为卡牌面值字符 
        int index = static_cast<int>(face);
        // 校验是否在枚举范围
        if (index < 0 || index >= static_cast<int>(CardFaceType::CFT_NUM_CARD_FACE_TYPES)) {
            return ""; 
        }

        const std::string faceStrs[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
        return faceStrs[index];
    }

    static std::string suitToColor(CardSuitType suit) { // 根据花色返回仅出现的卡牌颜色，以便组成路径地址
        if (suit == CardSuitType::CST_CLUBS || suit == CardSuitType::CST_SPADES) {
            return "black";
        }
        else {
            return "red";
        }
    }
};

#endif