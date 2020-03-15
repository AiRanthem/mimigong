#ifndef __NPC_H__
#define __NPC_H__
#include "cocos2d.h"
USING_NS_CC;

class NPC : public Sprite
{
public:
	virtual bool init();
	// ״̬
	bool active;
	CREATE_FUNC(NPC);
	// ����
	Animate * walkUp;
	Animate * walkLeft;
	Animate * walkRight;
	Animate * walkDown;
private:

	// ��ʼ֡
	SpriteFrame* frameOriginal;

};

#endif // !__NPC_H__
