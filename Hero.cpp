#include "Hero.h"
#include "Common.h"

bool Hero::init()
{
	/*行走动画*/
	auto HeroTexture = TextureCache::sharedTextureCache()->addImage("Red.png");

	cocos2d::Vector<cocos2d::SpriteFrame*> framesUp;
	cocos2d::Vector<cocos2d::SpriteFrame*> framesDown;
	cocos2d::Vector<cocos2d::SpriteFrame*> framesLeft;
	cocos2d::Vector<cocos2d::SpriteFrame*> framesRight;

	// 将帧存入数组
	SpriteFrame* frame = NULL;
	frameOriginal = NULL;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			frame = SpriteFrame::createWithTexture(HeroTexture, Rect(48 * j, 64 * i + 16, 48, 48));
			if (i == 0 && j == 0)
				frameOriginal = frame;
			if (i == 0)
				framesDown.pushBack(frame);
			else if (i == 1)
				framesLeft.pushBack(frame);
			else if (i == 2)
				framesRight.pushBack(frame);
			else if (i == 3)
				framesUp.pushBack(frame);
		}
	}
	// 按照初始帧初始化
	Sprite::initWithSpriteFrame(frameOriginal);
	// 创建帧动画
	walkUp = Animate::create(Animation::createWithSpriteFrames(framesUp, 0.1f));
	walkDown = Animate::create(Animation::createWithSpriteFrames(framesDown, 0.1f));
	walkLeft = Animate::create(Animation::createWithSpriteFrames(framesLeft, 0.1f));
	walkRight = Animate::create(Animation::createWithSpriteFrames(framesRight, 0.1f));
	walkUp->retain();
	walkDown->retain();
	walkLeft->retain();
	walkRight->retain();

	/*跑动动画*/
	// 清空数组
	framesUp.clear();
	framesRight.clear();
	framesDown.clear();
	framesLeft.clear();
	// 再存入跑动动画
	auto RunTexture = TextureCache::sharedTextureCache()->addImage("RedRun.png");
	frame = NULL;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			frame = SpriteFrame::createWithTexture(RunTexture, Rect(48 * j, 64 * i + 16, 48, 48));
			if (i == 0)
				framesDown.pushBack(frame);
			else if (i == 1)
				framesLeft.pushBack(frame);
			else if (i == 2)
				framesRight.pushBack(frame);
			else if (i == 3)
				framesUp.pushBack(frame);
		}
	}
	// 创建帧动画
	runUp = Animate::create(Animation::createWithSpriteFrames(framesUp, 0.1f));
	runDown = Animate::create(Animation::createWithSpriteFrames(framesDown, 0.1f));
	runLeft = Animate::create(Animation::createWithSpriteFrames(framesLeft, 0.1f));
	runRight = Animate::create(Animation::createWithSpriteFrames(framesRight, 0.1f));
	runUp->retain();
	runDown->retain();
	runLeft->retain();
	runRight->retain();

	/*添加键盘监听*/
	auto kbListener = EventListenerKeyboard::create();
	kbListener->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, this);
	kbListener->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(kbListener, this);

	/*其他信息获取以及设置锚点*/
	vX = 0;
	vY = 0;
	width = getContentSize().width;
	height = getContentSize().height;
	setAnchorPoint(Vec2(0.5, 0.5));

	/*状态标识*/
	direction = MOVE_DOWN;
	wantDiscover = false;
	isWalking = false;
	isRunning = false;
	keynum = 0;
	return true;
}

void Hero::move(float dt)
{
	int speed = isRunning ? 10 : 5;
	if (direction)
	{
		auto x = getPositionX();
		auto y = getPositionY();
		if (isWalking)
			switch (direction)
			{
			case MOVE_UP:
				if (y <= vY - height / 2)
					setPosition(x, y + speed);
				break;
			case MOVE_LEFT:
				if (x >= width / 2)
					setPosition(x - speed, y);
				break;
			case MOVE_DOWN:
				if (y >= height / 2)
					setPosition(x, y - speed);
				break;
			case MOVE_RIGHT:
				if (x <= vX - width / 2)
					setPosition(x + speed, y);
				break;
			}
	}
}

void Hero::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		stopAllActions();
		isWalking=true;
		direction = MOVE_UP;
		if (isRunning)
			runAction(RepeatForever::create(runUp));
		else
			runAction(RepeatForever::create(walkUp));
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		stopAllActions();
		isWalking = true;
		direction = MOVE_DOWN;
		if (isRunning)
			runAction(RepeatForever::create(runDown));
		else
			runAction(RepeatForever::create(walkDown));
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		stopAllActions();
		isWalking = true;
		direction = MOVE_LEFT;
		if (isRunning)
			runAction(RepeatForever::create(runLeft));
		else
			runAction(RepeatForever::create(walkLeft));
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		stopAllActions();
		isWalking = true;
		direction = MOVE_RIGHT;
		if (isRunning)
			runAction(RepeatForever::create(runRight));
		else
			runAction(RepeatForever::create(walkRight));
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		wantDiscover = true;
		break;
	case EventKeyboard::KeyCode::KEY_Z:
	case EventKeyboard::KeyCode::KEY_CAPITAL_Z:
		isRunning = true;
		if (isWalking)
		{
			stopAllActions();
			switch (direction) 
			{
			case MOVE_UP:
				runAction(RepeatForever::create(runUp));
				break;
			case MOVE_DOWN:
				runAction(RepeatForever::create(runDown));
				break;
			case MOVE_LEFT:
				runAction(RepeatForever::create(runLeft));
				break;
			case MOVE_RIGHT:
				runAction(RepeatForever::create(runRight));
				break;
			}
		}
		break;
	}
}

void Hero::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_Z || keyCode == EventKeyboard::KeyCode::KEY_CAPITAL_Z)
	{
		isRunning = false;
		if (isWalking)
		{
			stopAllActions();
			switch (direction)
			{
			case MOVE_UP:
				runAction(RepeatForever::create(walkUp));
				break;
			case MOVE_DOWN:
				runAction(RepeatForever::create(walkDown));
				break;
			case MOVE_LEFT:
				runAction(RepeatForever::create(walkLeft));
				break;
			case MOVE_RIGHT:
				runAction(RepeatForever::create(walkRight));
				break;
			}
		}
	}
	else
	{
		stopAllActions();
		wantDiscover = false;
		isWalking = false;
	}
}

void Hero::getMapSize(float x, float y)
{
	vX = x;
	vY = y;
}

bool Hero::canMeetEnd()
{
	if (keynum == 3)
		return true;
	else
		return false;
}

void Hero::getKey()
{
	++keynum;
}

int Hero::keys()
{
	return keynum;
}