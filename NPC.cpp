#include "NPC.h"

bool NPC::init()
{
	/*���߶���*/
	auto HeroTexture = TextureCache::sharedTextureCache()->addImage("001.png");

	cocos2d::Vector<cocos2d::SpriteFrame*> framesUp;
	cocos2d::Vector<cocos2d::SpriteFrame*> framesDown;
	cocos2d::Vector<cocos2d::SpriteFrame*> framesLeft;
	cocos2d::Vector<cocos2d::SpriteFrame*> framesRight;

	// ��֡��������
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
	// ���ճ�ʼ֡��ʼ��
	if (!Sprite::initWithSpriteFrame(frameOriginal))
		return false;
	// ����֡����
	walkUp = Animate::create(Animation::createWithSpriteFrames(framesUp, 0.1f));
	walkDown = Animate::create(Animation::createWithSpriteFrames(framesDown, 0.1f));
	walkLeft = Animate::create(Animation::createWithSpriteFrames(framesLeft, 0.1f));
	walkRight = Animate::create(Animation::createWithSpriteFrames(framesRight, 0.1f));
	walkUp->retain();
	walkDown->retain();
	walkLeft->retain();
	walkRight->retain();

	/*������Ϣ��ȡ�Լ�����ê��*/
	setAnchorPoint(Vec2(0.5, 0.5));
	active = false;
}
