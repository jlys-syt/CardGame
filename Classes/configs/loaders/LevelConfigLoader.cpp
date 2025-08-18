#include "LevelConfigLoader.h"

int LevelConfigLoader::uniqueId = 0; //��ʼ��

 // ����json�ַ�������ȡÿ������Ŀ�Ƭ����
LevelConfig* LevelConfigLoader::loadLevelConfig(std::string fileName)
{
	uniqueId = 0; // ����
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
		for (int i = 0; i < playField.Size(); ++i) // �����ڲ��������
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
		for (int i = 0; i < stackFiled.Size(); ++i) // �����ڲ��������
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

 // ��ȡ��Ƭ���������ֵ������ CardModel ���󣬴洢�� Levelconfig �������Ӧ������
bool LevelConfigLoader::parseToCardModel(rapidjson::Value& cardInfo, std::vector<CardModel>& cards, CardZone zone)
{
	// �жϷǷ����������ӽ�׳��
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

	// ��ȡԭʼ���ݣ�����ö��Խ���ж�
	int faceInt = cardInfo["CardFace"].GetInt();
	int suitInt = cardInfo["CardSuit"].GetInt();
	float x = position["x"].GetFloat();
	float y = position["y"].GetFloat();

	if (faceInt < 0 || faceInt > 12) return false;
	if (suitInt < 0 || suitInt > 3) return false;

	CardFaceType faceType = static_cast<CardFaceType>(faceInt);
	CardSuitType suitType = static_cast<CardSuitType>(suitInt);
	cocos2d::Vec2 pos(x, y);

	// ����CardModel���󣬱�������Ӧ����������
	int id = uniqueId++;
	static int offset = -35; // ���Ƶĳ�ʼƫ��ֵΪ -35 + 35
	if (zone == CardZone::Stack) {
		offset += 35; // ��һ�ű�ǰһ������ƫ�� 35
		pos += Vec2(190 + offset, 160); // ���ǵ���ͬ�����ƫ��
	}
	else pos += Vec2(-100, -120);
	cards.emplace_back(id, zone, pos, suitType, faceType); // ֱ�ӵ��ù��죬������˹���Ϳ�����ʱ������
	return true;
}