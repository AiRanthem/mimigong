#ifndef __END_SCENE_H__
#define __END_SCENE_H__
#include "cocos2d.h"
#include "Hero.h"
#include "NPC.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

class End : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();
	
	virtual void update(float);

	CREATE_FUNC(End);

private:
	Size mapSize;
	Size visibleSize;
	Size tileSize;
	float heroPosX, heroPosY;
	Hero* hero;
	NPC* npc1;
	Sprite* dialog;
	Sprite* title;
	Label* lab;
	TMXTiledMap* map;
	CocosDenshion::SimpleAudioEngine * audio;
	//µØÍ¼²ã
	TMXLayer * collisionLayer;
	TMXObjectGroup * objects;


	bool isTelling;
	bool fly;
	void tellYouSomething(const char *);
	void goon(EventKeyboard::KeyCode keyCode, Event* event);
	void gameEnd();
	bool ended;
};


#endif // !__ENDSCENE_H__

