#include "PageSceneTest.h"
USING_NS_CC;

bool PageSceneTest::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		//add close button
		CCMenuItemImage* pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(PageSceneTest::menuCloseCallback));
		CC_BREAK_IF(!pCloseItem);
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		CC_BREAK_IF(!pMenu);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);

		//add words
		CCLabelTTF* pLabel = CCLabelTTF::create("PageScene", "Arial", 24);
		CC_BREAK_IF(!pLabel);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pLabel->setPosition(ccp(size.width / 2, size.height - 50));
		this->addChild(pLabel, 1);

		addimage();

		bRet = true;
	}while(0);
	
	return bRet;
}

void PageSceneTest::addimage()
{
	do 
	{
		//add background image
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSprite* pSprite = CCSprite::create("HelloWorld.png");
		CC_BREAK_IF(!pSprite);
		pSprite->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(pSprite);
		CCActionInterval* actionto = CCMoveTo::create(2,CCPointMake(size.width / 4, size.height / 4));
		pSprite->runAction(actionto);
	} while (0);
}

CCScene* PageSceneTest::scene()
{
	CCScene* pScene = NULL;
	do 
	{
		pScene = CCScene::create();
		CC_BREAK_IF(!pScene);

		PageSceneTest* pLayer = PageSceneTest::create();
		CC_BREAK_IF(!pLayer);

		pScene->addChild(pLayer);
	} while (0);

	return pScene;
}

void PageSceneTest::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}
