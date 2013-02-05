#include "PageScene.h"
USING_NS_CC;

bool PageScene::init()
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
			menu_selector(PageScene::menuCloseCallback));
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

void PageScene::addimage()
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

CCScene* PageScene::scene()
{
	CCScene* pScene = NULL;
	do 
	{
		pScene = CCScene::create();
		CC_BREAK_IF(!pScene);

		PageScene* pLayer = PageScene::create();
		CC_BREAK_IF(!pLayer);

		pScene->addChild(pLayer);
	} while (0);

	return pScene;
}

void PageScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}
