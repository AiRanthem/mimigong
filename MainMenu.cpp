#include "MainMenu.h"
#include "GameWorldScene.h"

Scene* MainMenu::createScene()
{
	return MainMenu::create();
}

bool MainMenu::init()
{
	if (!Scene::init())
		return false;
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	// BGM
	audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("OP.mp3");
	audio->setBackgroundMusicVolume(5);
	audio->playBackgroundMusic("OP.mp3", true);

	// 背景图片
	auto backGround = Sprite::create("background_faded.jpg");
	backGround->setAnchorPoint(Vec2(0, 0));
	backGround->setContentSize(visibleSize);
	addChild(backGround, 0);

	// 菜单栏
	auto bar = Sprite::create("bar.png");
	bar->setAnchorPoint(Vec2(0.5, 0.5));
	bar->setPosition(visibleSize.width - 200, visibleSize.height / 2);
	bar->setOpacity(155);
	auto barSize = Size(250,700);
	bar->setContentSize(barSize);
	addChild(bar, 1);


	// 创建菜单按钮
	auto gameStart = MenuItemImage::create(
		"button.png",
		"button.png",
		CC_CALLBACK_1(MainMenu::gameStartCallBack, this));
	gameStart->setContentSize(Size(barSize.width * 2 / 3, barSize.width * 2 / 3));
	gameStart->setPosition(bar->getPositionX(), bar->getPositionY() + gameStart->getContentSize().height);

	auto gameManual = MenuItemImage::create(
		"button.png",
		"button.png",
		CC_CALLBACK_1(MainMenu::manualCallback, this));
	gameManual->setContentSize(Size(barSize.width * 2 / 3, barSize.width * 2 / 3));
	gameManual->setPosition(bar->getPositionX(), bar->getPositionY());

	auto gameEnd = MenuItemImage::create(
		"button.png",
		"button.png",
		CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
	gameEnd->setContentSize(Size(barSize.width * 2 / 3, barSize.width * 2 / 3));
	gameEnd->setPosition(bar->getPositionX(), bar->getPositionY() - gameStart->getContentSize().height);


	// 添加菜单
	auto menu = Menu::create(gameStart, gameManual,gameEnd, NULL);
	menu->setPosition(Point::ZERO);
	addChild(menu, 2);

	//添加标签
	auto startLabel = Label::createWithSystemFont(FontToUTF8("开始游戏"), "Microsoft YaHei UI", 20);
	startLabel->setAnchorPoint(Vec2(0.5, 0.8));
	startLabel->setPosition(gameStart->getPosition());
	addChild(startLabel, 3);

	auto manualLabel = Label::createWithSystemFont(FontToUTF8("游戏指南"), "Microsoft YaHei UI", 20);
	manualLabel->setAnchorPoint(Vec2(0.5, 0.8));
	manualLabel->setPosition(gameManual->getPosition());
	addChild(manualLabel, 3);

	auto closeLabel = Label::createWithSystemFont(FontToUTF8("退出游戏"), "Microsoft YaHei UI", 20);
	closeLabel->setAnchorPoint(Vec2(0.5, 0.8));
	closeLabel->setPosition(gameEnd->getPosition());
	addChild(closeLabel, 3);

	// 标题
	auto title = Sprite::create("title.png");
	title->setScale(0.4);
	title->setAnchorPoint(Vec2(0.5, 0.5));
	title->setPosition(visibleSize.width / 2 - 150, visibleSize.height / 2 - 50);
	title->setOpacity(0);
	addChild(title, 3);
	auto fadein = FadeIn::create(2);
	auto moveup = MoveBy::create(2, Vec2(0, 50));
	title->runAction(Spawn::create(fadein, moveup, nullptr));

	return true;
}

void MainMenu::gameStartCallBack(cocos2d::Ref* pSender)
{
	audio->stopBackgroundMusic();
	// 创建场景
	auto scene = GameWorld::createScene();
	// 让导演替换现在的场景
	Director::getInstance()->replaceScene(scene);
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainMenu::manualCallback(Ref* pSender)
{
	audio->stopBackgroundMusic();
	auto scene = Manual::createScene();
	Director::getInstance()->replaceScene(scene);
}
