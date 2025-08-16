#include "GameView.h"

GameView* GameView::create(GameModel& model){
	GameView* pGameView = new (std::nothrow) GameView;
	if (pGameView && pGameView->init(model)){
		pGameView->autorelease(); // 内存池自动释放
		return pGameView;
	}
	CC_SAFE_DELETE(pGameView);
	return nullptr;
}

 // 初始化
bool GameView::init(GameModel& model){
	if (!Node::init()){
		return false;
	}
	_cardController = new CardController(model); // 生成卡片管理器对象，用于回调函数中实现处理逻辑
	generateCardViews(model);

	_backLabel = cocos2d::Label::createWithSystemFont(u8"回退", "Microsoft YaHei", 36); // 标签设置
	//_backLabel->setPosition(900, 400);
	_backLabel->setPosition(680,110);
	_backLabel->setTextColor(cocos2d::Color4B::WHITE);
	this->addChild(_backLabel, 100);

	registerTouchEvent(); // 给当前卡片视图注册触摸事件
    return true;
}

 // 生成卡片视图，初始化，并将指向的指针放在游戏视图对应的容器里
void GameView::generateCardViews(GameModel& model) {	
	// 卡片视图绑定回调
	auto handleCardClick = [this](CardView* cardView) {
		// 调用 GameController 处理卡牌点击逻辑
		CardModel& cardModel = cardView->_cardManager->getModel();
		if (cardModel.getZone() == CardZone::Playfield) {
			_cardController->selectCardFromPlayefieldAndMatch(cardModel);
		}
		else if (cardModel.getZone() == CardZone::Stack) {
			_cardController->clickStackCard(cardModel);
		}
	};

    // 生成 playfield 区域的卡片视图，并绑定回调函数
    const auto& playfield = model.getPlayfield();
    for (auto& cardModel : playfield) {
        CardView* cardView = CardView::create(cardModel, Vec2(0, 0));
        if (cardView) {
            _playfieldCardViews.push_back(cardView);
            cardView->setClickCallback(handleCardClick);
            this->addChild(cardView);
        }
    }
   
    // 生成 stackfield 区域的卡片视图，并绑定回调函数
    const auto& stackfield = model.getStackfield();
    for (auto& cardModel : stackfield) {
        CardView* cardView = CardView::create(cardModel, Vec2(0, 0));
        if (cardView) {
            _stackfieldCardViews.push_back(cardView);
            cardView->setClickCallback(handleCardClick);
            this->addChild(cardView);
        }
    }
}

// 注册 backLabel 标签的触摸事件
void GameView::registerTouchEvent() {
	cocos2d::EventListenerTouchOneByOne* listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event)->bool {
		cocos2d::Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
		if (_backLabel->getBoundingBox().containsPoint(touchPos)){
			_backLabel->setScale(1.2f);			
			return true;
		}
		return false;
	};

	listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
		_backLabel->setScale(1.0f);
		cocos2d::Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
		if (_backLabel->getBoundingBox().containsPoint(touchPos)) {
			onClickedLabel();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

 // 标签点击后的处理函数
void GameView::onClickedLabel() {
	CCLOG(u8"Label 被点击");
	_cardController->handleLabelClick();
}