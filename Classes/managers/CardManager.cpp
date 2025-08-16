#include "CardManager.h"
#include "../views/CardView.h"
#include "../services/CardIdManagerMap.h"

CardManager::CardManager(const CardModel& model) : _model(model), _view(nullptr), _isSelected(false) {
    CardIdManagerMap::getInstance().addCardManager(model.getCardId(), this);
}

CardManager::~CardManager() {}

 // 视图指针和数据模型的初始化，向模型 id 和 CardManager 管理器的映射 map 表中进行注册，
void CardManager::setCard(const CardModel& model, CardView* view) { 
    _model = model;
    _view = view;
    CardIdManagerMap::getInstance().addCardManager(model.getCardId(), this);
    setupTouchEvents();
}

void CardManager::setupTouchEvents() {
    if (!_view) return;
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(CardManager::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(CardManager::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(CardManager::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(CardManager::onTouchCancelled, this);

    _view->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, _view);
}

bool CardManager::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return false;
    cocos2d::Vec2 touchPos = _view->convertToNodeSpace(touch->getLocation());
    if (!_view->containsPoint(touchPos)) return false;
    _view->setScale(1.1f);
    _isSelected = true;
    return true;
}

void CardManager::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    // 可添加拖动逻辑
}

void CardManager::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return;
    cocos2d::Vec2 touchPos = _view->convertToNodeSpace(touch->getLocation());
    _view->setScale(1.0f);  // 恢复原大小
    if (_cardClickedCallback) {
        CCLOG(u8"触发卡片点击回调");
        _cardClickedCallback();
    }
    _isSelected = false;
}

void CardManager::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return;
    _view->setScale(1.0f);
    _isSelected = false;
}

void CardManager::setCardClickedCallback(const std::function<void()>& callback) {
    _cardClickedCallback = callback;
}