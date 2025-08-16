#include "LevelConfigLoader.h"

int LevelConfigLoader::uniqueId = 0; //初始化

 // 解析json字符串，提取每个区域的卡片对象
LevelConfig* LevelConfigLoader::loadLevelConfig(std::string fileName)
{
	uniqueId = 0; // 重置
	std::string jsonStr = FileUtils::getInstance()->getStringFromFile(fileName);
	rapidjson::Document doc;
	doc.Parse(jsonStr.c_str());
	if (doc.HasParseError())
	{
		CCLOG(u8"json parse is failed! %s\n", doc.GetParseError());
		return nullptr;
	}

	if (!doc.IsObject())
	{
		CCLOG(u8"doc not is a Object!");
		return nullptr;
	}
	
	LevelConfig* config = new LevelConfig;
	if (doc.HasMember("Playfield") && doc["Playfield"].IsArray())
	{
		rapidjson::Value& playField =  doc["Playfield"];
		for (int i = 0; i < playField.Size(); ++i) // 遍历内层对象数组
		{
			if (!LevelConfigLoader::parseToCardModel(playField[i], config->_playfieldCards, CardZone::Playfield))
			{
				CCLOG(u8"playFiled[%d] is not an Object!", i);
				return nullptr;
			}
		}		
	}

	if (doc.HasMember("Stack") && doc["Stack"].IsArray())
	{
		rapidjson::Value& stackFiled = doc["Stack"];
		for (int i = 0; i < stackFiled.Size(); ++i) // 遍历内层对象数组
		{
			if (!LevelConfigLoader::parseToCardModel(stackFiled[i], config->_stackCards, CardZone::Stack))
			{
				CCLOG(u8"stackFiled[%d] is not an Object!", i);
				return nullptr;
			}
		}		
	}
	return config;
}

 // 提取卡片对象的属性值，生成 CardModel 对象，存储在 Levelconfig 里面的相应容器里
bool LevelConfigLoader::parseToCardModel(rapidjson::Value& cardInfo, std::vector<CardModel>& cards, CardZone zone)
{
	// 判断非法条件，增加健壮性
	if (!cardInfo.IsObject())
	{
		return false;
	}

	if (!cardInfo.HasMember("CardFace") || !cardInfo["CardFace"].IsInt()) { return false; }
	if (!cardInfo.HasMember("CardSuit") || !cardInfo["CardSuit"].IsInt()) { return false; }
	if (!cardInfo.HasMember("Position") || !cardInfo["Position"].IsObject()) return false;

	const rapidjson::Value& position = cardInfo["Position"];
	if (!position.HasMember("x") || !position["x"].IsInt()) { return false; }
	if (!position.HasMember("y") || !position["y"].IsInt()) { return false; }

	// 提取原始数据，进行枚举越界判断
	int faceInt = cardInfo["CardFace"].GetInt();
	int suitInt = cardInfo["CardSuit"].GetInt();
	float x = position["x"].GetFloat();
	float y = position["y"].GetFloat();

	if (faceInt < 0 || faceInt > 12) return false;
	if (suitInt < 0 || suitInt > 3) return false;

	CardFaceType faceType = static_cast<CardFaceType>(faceInt);
	CardSuitType suitType = static_cast<CardSuitType>(suitInt);
	cocos2d::Vec2 pos(x, y);

	// 构造CardModel对象，保存在相应区域容器里
	int id = uniqueId++;
	static int offset = -35; // 堆牌的初始偏移值为 -35 + 35
	if (zone == CardZone::Stack) {
		offset += 35; // 后一张比前一张向右偏移 35
		pos += Vec2(190 + offset, 160); // 考虑到不同区域的偏移
	}
	else pos += Vec2(-100, -120);
	cards.emplace_back(id, zone, pos, suitType, faceType); // 直接调用构造，相对少了构造和拷贝临时生成量
	return true;
}