#include "EndScene.h"
#include "Common.h"

Scene* End::createScene()
{
	return End::create();
}

bool End::init()
{
	if (!Scene::init())
		return false;
	
	visibleSize = Director::getInstance()->getVisibleSize();
	// 添加地图
	map = TMXTiledMap::create("end.tmx");
	this->addChild(map, 0);
	mapSize = map->getMapSize();
	tileSize = map->getTileSize();
	objects = map->getObjectGroup("Objects");
	collisionLayer = map->layerNamed("Collision");
	collisionLayer->setVisible(false);

	// 创建主角
	hero = Hero::create();
	map->addChild(hero, 2);
	auto heroPos = objects->getObject("heroPos");
	float x = heroPos["x"].asFloat();
	float y = heroPos["y"].asFloat();
	hero->setPosition(x, y);
	hero->getMapSize(mapSize.width*tileSize.width, mapSize.height*tileSize.height);

	// 添加NPC
	npc1 = NPC::create();
	auto npcPos = objects->getObject("NPC");
	x = npcPos["x"].asFloat();
	y = npcPos["y"].asFloat();
	npc1->setPosition(x, y);
	addChild(npc1, 2);

	// 标题
	title = Sprite::create("title.png");
	title->setScale(0.6);
	title->setOpacity(0);
	title->setAnchorPoint(Vec2(0.5, 0.5));
	title->setPosition(hero->getPosition());
	addChild(title, 10);

	// 演出
	tellYouSomething("恭喜你，这一切都是你的！");
	audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("ED.mp3");
	audio->setBackgroundMusicVolume(5);
	
	fly = false;
	isTelling = false;
	ended = false;

	scheduleUpdate();
	return true;
}

void End::update(float dt)
{
	/*判断障碍物*/
	// 获取坐标
	int foreX = hero->getPositionX() / tileSize.width;
	int foreY = (mapSize.height*tileSize.height - hero->getPositionY()) / tileSize.height;
	int curX = foreX;
	int curY = foreY;
	switch (hero->direction)
	{
	case MOVE_UP:
		foreY -= 1; break;
	case MOVE_DOWN:
		foreY += 1; break;
	case MOVE_LEFT:
		foreX -= 1; break;
	case MOVE_RIGHT:
		foreX += 1; break;
	}
	foreX = foreX > 0 ? foreX : 0;
	foreX = foreX < mapSize.width - 1 ? foreX : mapSize.width - 1;
	foreY = foreY > 0 ? foreY : 0;
	foreY = foreY < mapSize.height - 1 ? foreY : mapSize.height - 1;

	int fgid = collisionLayer->tileGIDAt(Vec2(foreX, foreY));
	switch (fgid)
	{
	case 331:
		// NPC交互
		if (hero->wantDiscover)
		{
			switch (hero->direction)
			{
			case MOVE_UP:
				npc1->runAction(npc1->walkDown->clone());
				break;
			case MOVE_DOWN:
				npc1->runAction(npc1->walkUp->clone());
				break;
			case MOVE_LEFT:
				npc1->runAction(npc1->walkRight->clone());
				break;
			case MOVE_RIGHT:
				npc1->runAction(npc1->walkLeft->clone());
				break;
			}
			tellYouSomething("你终于还是选择了来到这里");
		}
		break;
	case 336:
		// 飞
		if (hero->wantDiscover)
		{
			if(!audio->isBackgroundMusicPlaying())
				audio->playBackgroundMusic("ED.mp3",true);
			hero->setVisible(false);
			fly = true;
			
			if (ended)
				title->runAction(FadeIn::create(10));
			else
				ended = true;
		}
		break;
	}
	if (!fgid || fly)
		hero->move();

	/*场景随主角移动*/
	double screenX = MAX(hero->getPositionX(), visibleSize.width / 2);
	double screenY = MAX(hero->getPositionY(), visibleSize.height / 2);
	screenX = MIN(screenX, mapSize.width*tileSize.width - visibleSize.width / 2);
	screenY = MIN(screenY, mapSize.height*tileSize.height - visibleSize.height / 2);

	setPosition(visibleSize.width / 2 - screenX, visibleSize.height / 2 - screenY);
	title->setPosition(screenX,screenY);
}

void End::tellYouSomething(const char * words)
{
	if (isTelling)
		return;
	isTelling = true;
	// 转换为UTF-8
	auto utf8_words = FontToUTF8(words);

	// 对话框
	dialog = Sprite::create("menu_long.jpg");
	dialog->setAnchorPoint(Vec2(0.5, 0.5));

	int x = MAX(hero->getPositionX(), visibleSize.width / 2);
	int y = MAX(hero->getPositionY(), visibleSize.height / 2);
	x = MIN(x, mapSize.width*tileSize.width - visibleSize.width / 2);
	y = MIN(y, mapSize.height*tileSize.height - visibleSize.height / 2);

	dialog->setPosition(x, y - visibleSize.height / 3);
	addChild(dialog, 4);
	auto diaSize = dialog->getContentSize();
	// 文本内容
	lab = Label::createWithSystemFont(utf8_words, "Microsoft YaHei UI", 24);
	lab->setAnchorPoint(Vec2(0.5, 0.5));
	lab->setPosition(dialog->getPosition());
	addChild(lab, 5);

	// 监听器
	auto cont = EventListenerKeyboard::create();
	cont->onKeyPressed = CC_CALLBACK_2(End::goon, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(cont, this);

}

void End::goon(EventKeyboard::KeyCode keyCode, Event* event)
{
	removeChild(lab);
	removeChild(dialog);
	isTelling = false;
}

