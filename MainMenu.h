#pragma once
#ifndef  __MAINMENU_H__
#define __MAINMENU_H__
#include "cocos2d.h"
#include "Common.h"
#include "SimpleAudioEngine.h"
#include "Manual.h"
USING_NS_CC;
class MainMenu:public Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void gameStartCallBack(cocos2d::Ref* pSender);
	void menuCloseCallback(Ref* pSender);
	void manualCallback(Ref* pSender);
	CREATE_FUNC(MainMenu);
private:
	CocosDenshion::SimpleAudioEngine * audio;
};

#endif // ! __MAINMENU_H__
