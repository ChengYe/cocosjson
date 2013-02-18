#ifndef __PAGE_SCENE_H__
#define __PAGE_SCENE_H__

#include "cocos2d.h"

class PageSceneTest : public cocos2d::CCLayer
{
public:
	virtual bool init();

	void addimage();

	static cocos2d::CCScene* scene();

	void menuCloseCallback(CCObject* pSender);

	CREATE_FUNC(PageSceneTest);
};

#endif