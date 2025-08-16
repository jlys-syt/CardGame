#include "CardManager.h"
#include "../views/CardView.h"
#include "../services/CardIdManagerMap.h"

CardManager::CardManager(const CardModel& model) : _model(model), _view(nullptr) {
    CardIdManagerMap::getInstance().addCardManager(model.getCardId(), this);
}

CardManager::~CardManager() {}

 // ��ͼָ�������ģ�͵ĳ�ʼ������ģ�� id �� CardManager ��������ӳ�� map ���н���ע�ᣬ
void CardManager::setCard(const CardModel& model, CardView* view) { 
    _model = model;
    _view = view;
    CardIdManagerMap::getInstance().addCardManager(model.getCardId(), this);
    setTouchEvents();
}

 // �󶨴����¼�
void CardManager::setTouchEvents() {
    if (!_view) return;
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(CardManager::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(CardManager::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(CardManager::onTouchCancelled, this);

    _view->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, _view);
}

 // ������ʼ�������Ŵ󱻵���Ŀ�Ƭ
bool CardManager::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return false;
    cocos2d::Vec2 touchPos = _view->convertToNodeSpace(touch->getLocation());
    if (!_view->containsPoint(touchPos)) return false;
    _view->setScale(1.1f);
    return true;
}

// ��������������ִ�лص�����
void CardManager::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return;
    cocos2d::Vec2 touchPos = _view->convertToNodeSpace(touch->getLocation());
    _view->setScale(1.0f);  // �ָ�ԭ��С
    if (_cardClickedCallback) {
        CCLOG(u8"������Ƭ����ص�");
        _cardClickedCallback();
    }
}

 // ����ȡ������Ƭ�ظ�ԭ״
void CardManager::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return;
    if (_view->containsPoint(touch->getLocation()))
        _view->setScale(1.0f);
}

void CardManager::setCardClickedCallback(const std::function<void()>& callback) {
    _cardClickedCallback = callback;
}