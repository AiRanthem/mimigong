#ifndef __MANUAL_H__
#define __MANUAL_H__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Hero.h"
#include "MainMenu.h"
USING_NS_CC;

class Manual:public Scene
{
public:
	static Scene* createScene();

	virtual bool init();
	void goBack();
	void update(float);
	CREATE_FUNC(Manual);

private:
	CocosDenshion::SimpleAudioEngine * audio;
	Hero* hero;
};

#endif // !__MANUAL_H__
