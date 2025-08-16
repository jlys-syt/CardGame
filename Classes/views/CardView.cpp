#include "CardView.h"

CardView* CardView::create(const CardModel& model, const Vec2& offset) {
	CardView* pCardView = new CardView;
	if (pCardView && pCardView->init(model, offset)) {
		pCardView->autorelease(); // 内存池自动释放
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
        CCLOG(u8"加载资源失败!");
        return false;
    }

    _cardManager = new CardManager(model); 
    _cardManager->setCard(model, this); // 初始化指针和卡片模型引用，记录卡片和管理器的映射关系
    this->setPosition(model.getPosition() + offset); // 设置位置
    return true;
}

bool CardView::containsPoint(const cocos2d::Vec2& point) {
    if (!_background) 
        return false;
    return _background->getBoundingBox().containsPoint(point);
}
 
 // 加载背景图片
bool CardView::loadBackground() {
    _background = Sprite::create(CardResConfig::getBackGround());
    if (!_background) {
        CCLOG(u8"背景图片加载失败!");
        return false;
    }

    _background->setAnchorPoint(Vec2(0.5, 0.5));
    this->setContentSize(_background->getContentSize());
    this->addChild(_background);
    return true;
}

 // 加载小数字
bool CardView::loadSmallNumber(const CardModel& model) {
    auto suit = model.getSuitType();
    auto face = model.getFaceType();
    auto resPath = CardResConfig::getSmallNumberRes(suit, face);

    _smallNumber = Sprite::create(resPath);
    if (!_smallNumber){
        CCLOG(u8"小数字资源获取失败，path：%s", resPath);
        return false;
    }

    _smallNumber->setAnchorPoint(Vec2(0, 1));
    _smallNumber->setPosition(kSmallNumberPos);
    this->addChild(_smallNumber);
    return true;
}

 // 加载大数字
bool CardView::loadBigNumber(const CardModel& model) {
    auto suit = model.getSuitType();
    auto face = model.getFaceType();
    auto resPath = CardResConfig::getBigNumberRes(suit, face);

    _bigNumber = Sprite::create(resPath);
    if (!_bigNumber){
        CCLOG(u8"大数字资源获取失败，path：%s", resPath);
        return false;
    }

    _bigNumber->setAnchorPoint(Vec2(0.5, 0.5));
    _bigNumber->setPosition(KBigNumberPos);
    this->addChild(_bigNumber);
    return true;
}

 // 加载花色图标
bool CardView::loadSuitIcon(const CardModel& model) {
    auto suit = model.getSuitType();
    auto resPath = CardResConfig::getSuitRes(suit);

    _suitIcon = Sprite::create(resPath);
    if (!_suitIcon){
        CCLOG(u8"花色资源丢失 path: %s", resPath);
        return false;
    }

    _suitIcon->setAnchorPoint(Vec2(1, 1));
    _suitIcon->setPosition(kSuitIconPos);
    this->addChild(_suitIcon);
    return true;
}

 // 设置回调
void CardView::setClickCallback(const ClickCallback& callback) {
    _clickCallback = callback;
    _cardManager->setCardClickedCallback([this, callback]() {
        if (callback) {
            callback(this);
        }
    });
}