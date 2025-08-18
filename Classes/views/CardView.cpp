#include "CardView.h"

CardView* CardView::create(const CardModel& model, const Vec2& offset) {
	CardView* pCardView = new CardView;
	if (pCardView && pCardView->init(model, offset)) {
		pCardView->autorelease(); // �ڴ���Զ��ͷ�
		return pCardView;
	}
	return nullptr;
}

bool CardView::init(const CardModel& model, const Vec2& offset) {
    if (!Node::init()) {
        return false;
    }

    if (!loadBackground() || !loadSmallNumber(model) || !loadBigNumber(model) || !loadSuitIcon(model))
    {
        CCLOG(u8"������Դʧ��!");
        return false;
    }

    _cardManager = new CardManager(model); 
    _cardManager->setCard(model, this); // ��ʼ��ָ��Ϳ�Ƭģ�����ã���¼��Ƭ�͹�������ӳ���ϵ
    this->setPosition(model.getPosition() + offset); // ����λ��
    return true;
}

bool CardView::containsPoint(const cocos2d::Vec2& point) {
    if (!_background) 
        return false;
    return _background->getBoundingBox().containsPoint(point);
}
 
 // ���ر���ͼƬ
bool CardView::loadBackground() {
    _background = Sprite::create(CardResConfig::getBackGroundSrc());
    if (!_background) {
        CCLOG(u8"����ͼƬ����ʧ��!");
        return false;
    }

    _background->setAnchorPoint(Vec2(0.5, 0.5));
    this->setContentSize(_background->getContentSize());
    this->addChild(_background);
    return true;
}

 // ����С����
bool CardView::loadSmallNumber(const CardModel& model) {
    auto suit = model.getSuitType();
    auto face = model.getFaceType();
    auto resPath = CardResConfig::getSmallNumberSrc(suit, face);

    _smallNumber = Sprite::create(resPath);
    if (!_smallNumber){
        CCLOG(u8"С������Դ��ȡʧ�ܣ�path��%s", resPath);
        return false;
    }

    _smallNumber->setAnchorPoint(Vec2(0, 1));
    _smallNumber->setPosition(kSmallNumberPos);
    this->addChild(_smallNumber);
    return true;
}

 // ���ش�����
bool CardView::loadBigNumber(const CardModel& model) {
    auto suit = model.getSuitType();
    auto face = model.getFaceType();
    auto resPath = CardResConfig::getBigNumberSrc(suit, face);

    _bigNumber = Sprite::create(resPath);
    if (!_bigNumber){
        CCLOG(u8"��������Դ��ȡʧ�ܣ�path��%s", resPath);
        return false;
    }

    _bigNumber->setAnchorPoint(Vec2(0.5, 0.5));
    _bigNumber->setPosition(KBigNumberPos);
    this->addChild(_bigNumber);
    return true;
}

 // ���ػ�ɫͼ��
bool CardView::loadSuitIcon(const CardModel& model) {
    auto suit = model.getSuitType();
    auto resPath = CardResConfig::getSuitSrc(suit);

    _suitIcon = Sprite::create(resPath);
    if (!_suitIcon){
        CCLOG(u8"��ɫ��Դ��ʧ path: %s", resPath);
        return false;
    }

    _suitIcon->setAnchorPoint(Vec2(1, 1));
    _suitIcon->setPosition(kSuitIconPos);
    this->addChild(_suitIcon);
    return true;
}

 // ���ûص�
void CardView::setClickCallback(const ClickCallback& callback) {
    _clickCallback = callback;
    _cardManager->setCardClickedCallback([this, callback]() {
        if (callback) {
            callback(this);
        }
    });
}