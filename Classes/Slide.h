#pragma once

#include "cocos2d.h"
#include "DialogLayer.h"
#include "StatusLayer.h"
#include "Infolayer.h"
#include "WarLayer.h"
#include "SkillLayer.h"
#include "SkillToolLayer.h"
#include "LifeLayer.h"
#include "LeftTimeLayer.h"
#include "Util.h"

USING_NS_CC;

class Slide :public Layer
{
public:

	static Scene* createScene();
	static Slide* create(PhysicsWorld* world);

	bool init(PhysicsWorld* world);


	//音乐加载与播放
	void preloadMusic();
	void playBgm();
	void playEffect();


	void TouchEvent();

	void testKeyboardEvent();

	

	bool onConcactBegan(PhysicsContact& contact);


	void Schedule_(Ref *ref);
	void update(float f);
	void Slide::testOntouch();

	void Return(Ref *ref);
	void Restart(Ref *ref);
	void Exit(Ref *ref);

	//test
	EventListenerPhysicsContact * getTouchListener();

	// 修改瞬移样式
	void InstanceMove();

private:
	// 修改瞬移样式
	Sprite * instance_move_target = NULL;
	Point instanceMoveTarget;
	SkillToolLayer *skillToolLayer;
	LifeLayer * lifeLayer;
	LeftTimeLayer* leftTimeLayer;
	EventListenerPhysicsContact * touchListener;
	Slide();
	~Slide();
	EventDispatcher* dispatcher;

	MotionStreak* streak;

	Vec2 touch_pos;

	bool isTouching;
	bool isCut;
	int moveTimes;
	int bleed;
	float timesNow;
	int timeLeft;
	float difficalty;
	bool defence;
	int bomb;
	int shel;

	Sprite* player;
	Label *scoreLabel;
	Point oldPos;
	PhysicsWorld* m_world;
	Size visibleSize;
	Vector<PhysicsBody*> enemys;

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void newEnemys(float f);
	void addEnemy(int type, Point p);
	void addBonus();
	void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode code, Event* event);
	void bleedNew(int lose);
	void nodefence(float f);
	void escape();
	void gameOver();
};