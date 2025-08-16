#pragma once
#ifndef CARDRESCONFIG_H
#define CARDRESCONFIG_H
#include <string>
#include <array>
#include "LevelConfig.h"

/**
* @class CardResConfig
* @notos 根据加载的卡片模型的属性值获得相应资源的地址
* @duty 返回资源地址
* @scene 加载游戏资源
*/

class CardResConfig {
public:
    // 获取背景图片地址
    static std::string getBackGround() {
        return "res/card_general.png";
    }

    // 获取卡片花色地址
    static std::string getSuitRes(CardSuitType suit) {
        switch (suit) {
        case CardSuitType::CST_CLUBS:    return "res/suits/club.png";
        case CardSuitType::CST_DIAMONDS: return "res/suits/diamond.png";
        case CardSuitType::CST_HEARTS:   return "res/suits/heart.png";
        case CardSuitType::CST_SPADES:   return "res/suits/spade.png";
        default: return ""; // 处理非法枚举
        }
    }

    // 获得小数字地址
    static std::string getSmallNumberRes(CardSuitType suit, CardFaceType face) {
        std::string color = suitToColor(suit);
        std::string faceStr = faceToString(face);
        if (color.empty() || faceStr.empty()) {
            return "";
        }
        return "res/number/small_" + color + "_" + faceStr + ".png";
    }

    //获得大数字地址
    static std::string getBigNumberRes(CardSuitType suit, CardFaceType face) {
        std::string color = suitToColor(suit);
        std::string faceStr = faceToString(face);
        if (color.empty() || faceStr.empty()) {
            return "";
        }
        return "res/number/big_" + color + "_" + faceStr + ".png";
    }

private:
    static std::string faceToString(CardFaceType face) { // 转为字符串
        const std::string faceNames[] = {
        "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
        };

        int index = static_cast<int>(face);
        // 校验枚举范围
        if (index < 0 || index >= static_cast<int>(CardFaceType::CFT_NUM_CARD_FACE_TYPES)) {
            return ""; 
        }
        return faceNames[index];
    }

    static std::string suitToColor(CardSuitType suit) { // 转为字符串
        if (suit == CardSuitType::CST_CLUBS || suit == CardSuitType::CST_SPADES) {
            return "black";
        }
        else {
            return "red";
        }
    }
};

#endif