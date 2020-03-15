#pragma once
#include "cocos2d.h"
USING_NS_CC;
#ifndef _HERO_H_
#define _HERO_H_
#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4
class Hero : public Sprite
{
public:
	int direction;
	virtual bool init();
	void getMapSize(float,float);
	CREATE_FUNC(Hero);
	virtual void move(float=0);
	bool wantDiscover;
	bool isWalking;
	bool isRunning;
	bool canMeetEnd();
	void getKey();
	int keys();
private:
	// 动画
	Animate * walkUp;
	Animate * walkLeft;
	Animate * walkRight;
	Animate * walkDown;
	Animate * runUp;
	Animate * runLeft;
	Animate * runDown;
	Animate * runRight;
	
	// Size
	float vX;// 屏幕宽度高度
	float vY;
	float width;// 自身尺寸
	float height;

	// Keys
	int keynum;

	// 初始帧
	SpriteFrame* frameOriginal;

	// 监听回调函数
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};

#endif // !_HERO_H_


