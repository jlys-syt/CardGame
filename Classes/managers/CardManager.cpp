#include "CardManager.h"
#include "../views/CardView.h"
#include "../services/CardIdManagerMap.h"

CardManager::CardManager(const CardModel& model) : _model(model), _view(nullptr) {
    CardIdManagerMap::getInstance().addCardManager(model.getCardId(), this);
}

CardManager::~CardManager() {}

 // 视图指针和数据模型的初始化，向模型 id 和 CardManager 管理器的映射 map 表中进行注册，
void CardManager::setCard(const CardModel& model, CardView* view) { 
    _model = model;
    _view = view;
    CardIdManagerMap::getInstance().addCardManager(model.getCardId(), this);
    setTouchEvents();
}

 // 绑定触摸事件
void CardManager::setTouchEvents() {
    if (!_view) return;
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(CardManager::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(CardManager::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(CardManager::onTouchCancelled, this);

    _view->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, _view);
}

 // 触摸开始触发，放大被点击的卡片
bool CardManager::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return false;
    cocos2d::Vec2 touchPos = _view->convertToNodeSpace(touch->getLocation());
    if (!_view->containsPoint(touchPos)) return false;
    _view->setScale(1.1f);
    return true;
}

// 触摸结束触发，执行回调函数
void CardManager::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return;
    cocos2d::Vec2 touchPos = _view->convertToNodeSpace(touch->getLocation());
    _view->setScale(1.0f);  // 恢复原大小
    if (_cardClickedCallback) {
        CCLOG(u8"触发卡片点击回调");
        _cardClickedCallback();
    }
}

 // 触摸取消，卡片回复原状
void CardManager::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return;
    if (_view->containsPoint(touch->getLocation()))
        _view->setScale(1.0f);
}

void CardManager::setCardClickedCallback(const std::function<void()>& callback) {
    _cardClickedCallback = callback;
}