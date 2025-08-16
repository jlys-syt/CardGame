#include "GameView.h"

GameView* GameView::create(GameModel& model){
	GameView* pGameView = new (std::nothrow) GameView;
	if (pGameView && pGameView->init(model)){
		pGameView->autorelease(); // �ڴ���Զ��ͷ�
		return pGameView;
	}
	CC_SAFE_DELETE(pGameView);
	return nullptr;
}

 // ��ʼ��
bool GameView::init(GameModel& model){
	if (!Node::init()){
		return false;
	}
	_cardController = new CardController(model); // ���ɿ�Ƭ�������������ڻص�������ʵ�ִ����߼�
	generateCardViews(model);

	_backLabel = cocos2d::Label::createWithSystemFont(u8"����", "Microsoft YaHei", 36); // ��ǩ����
	//_backLabel->setPosition(900, 400);
	_backLabel->setPosition(680,110);
	_backLabel->setTextColor(cocos2d::Color4B::WHITE);
	this->addChild(_backLabel, 100);

	registerTouchEvent(); // ����ǰ��Ƭ��ͼע�ᴥ���¼�
    return true;
}

 // ���ɿ�Ƭ��ͼ����ʼ��������ָ���ָ�������Ϸ��ͼ��Ӧ��������
void GameView::generateCardViews(GameModel& model) {	
	// ��Ƭ��ͼ�󶨻ص�
	auto handleCardClick = [this](CardView* cardView) {
		// ���� GameController �����Ƶ���߼�
		CardModel& cardModel = cardView->_cardManager->getModel();
		if (cardModel.getZone() == CardZone::Playfield) {
			_cardController->selectCardFromPlayefieldAndMatch(cardModel);
		}
		else if (cardModel.getZone() == CardZone::Stack) {
			_cardController->clickStackCard(cardModel);
		}
	};

    // ���� playfield ����Ŀ�Ƭ��ͼ�����󶨻ص�����
    const auto& playfield = model.getPlayfield();
    for (auto& cardModel : playfield) {
        CardView* cardView = CardView::create(cardModel, Vec2(0, 0));
        if (cardView) {
            _playfieldCardViews.push_back(cardView);
            cardView->setClickCallback(handleCardClick);
            this->addChild(cardView);
        }
    }
   
    // ���� stackfield ����Ŀ�Ƭ��ͼ�����󶨻ص�����
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

// ע�� backLabel ��ǩ�Ĵ����¼�
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

 // ��ǩ�����Ĵ�����
void GameView::onClickedLabel() {
	CCLOG(u8"Label �����");
	_cardController->handleLabelClick();
}