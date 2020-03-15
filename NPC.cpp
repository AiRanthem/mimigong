#include "NPC.h"

bool NPC::init()
{
	/*行走动画*/
	auto HeroTexture = TextureCache::sharedTextureCache()->addImage("001.png");

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
			frame = SpriteFrame::createWithTexture(HeroTexture, Rect(32 * j, 50 * i, 32, 50));
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
	if (!Sprite::initWithSpriteFrame(frameOriginal))
		return false;
	// 创建帧动画
	walkUp = Animate::create(Animation::createWithSpriteFrames(framesUp, 0.1f));
	walkDown = Animate::create(Animation::createWithSpriteFrames(framesDown, 0.1f));
	walkLeft = Animate::create(Animation::createWithSpriteFrames(framesLeft, 0.1f));
	walkRight = Animate::create(Animation::createWithSpriteFrames(framesRight, 0.1f));
	walkUp->retain();
	walkDown->retain();
	walkLeft->retain();
	walkRight->retain();

	/*其他信息获取以及设置锚点*/
	setAnchorPoint(Vec2(0.5, 0.5));
	active = false;
}
