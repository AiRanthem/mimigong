#include "Manual.h"


Scene* Manual::createScene()
{
	return Manual::create();
}

bool Manual::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("mann.mp3", true);
	audio->setBackgroundMusicVolume(5);

	auto backGround = Sprite::create("manual.png");
	backGround->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(backGround, 0);

	hero = Hero::create();
	hero->setPosition(visibleSize.width / 3, visibleSize.height / 2);
	addChild(hero, 1);

	scheduleUpdate();

	return true;
}

void Manual::update(float dt)
{
	if (hero->wantDiscover)
		goBack();
}

void Manual::goBack()
{
	audio->stopBackgroundMusic();
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}