#ifndef  ADVENTURE_H_
#define  ADVENTURE_H_

#include "cocos2d.h"
#include "Slide.h"
#include "Global.h"
#include "DialogLayer.h"
#include "StatusLayer.h"
#include "Infolayer.h"
#include "WarLayer.h"
//#include "SkillLayer.h"
#include "Random.h"

#include <string>
#include <stdio.h> 
#include <iostream> 
#include <time.h> 


using namespace std;

USING_NS_CC;

#define database UserDefault::getInstance()

class Adventure :public Layer
{
public:
	Adventure();
	~Adventure();
	static cocos2d::Scene* scene();

	CREATE_FUNC(Adventure);

	virtual bool init();

	/*
	�洢���������vector��������
	wall������ǰ��
	stone����ʯ���ɼ�������ֵ
	monster1;����1
	monster2;����2
	black_hole;�ڶ����ɴ�����һ������ʤ���������������һ�ڶ���
	destination;�յ㣬�涴��־����������涴��һ�����ڶ���Χ����һ�����߼������Χ��
	random;����¼�
	supply;����վ
	*/
	Vector < Sprite * > v_wall;
	Vector < Sprite * > v_hero1;
	Vector < Sprite * > v_hero2;
	Vector < Sprite * > v_hero3;
	Vector < Sprite * > v_hero4;
	Vector < Sprite * > v_hero5;
	Vector < Sprite * > v_hero6;
	Vector < Sprite * > v_black_hole;
	Vector < Sprite * > v_destination;
	Vector < Sprite * > v_random;
	Vector < Sprite * > v_supply;

	void initTouchEvent();

	void loadObject();

	// ���������Ĳ�����װ�����ĺ���
	Vector <Sprite *> loadFromMap(TMXTiledMap* tmx, string obj, string name, int DisX, int DisY);

	//����player�ƶ��ĺ������������ݷ�װ��move()��
	void onRightPressed(Ref* sender);
	void onLeftPressed(Ref* sender);
	void onUpPressed(Ref* sender);
	void onDownPressed(Ref* sender);
	void move(Point direct);

	void judge(string object, Point nextPos);
	void fightJudge(Sprite* s, int num);
	void JumpRandom(Point);
	void levelJudge();
	void BlackHole(Point, int);

	int getLife() { return life; };
	int getAttack() { return attack; };
	int getLevel() { return level; };
	int getExp() { return experience; };
	
	void Restart(Ref* sender);
	void NextMap();
	void GameOver();

	bool win;

	// �����¼�
	void addKeyboardEvent();
	void keyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void keyRelease(EventKeyboard::KeyCode keyCode, Event *enent);
	//EventListenerKeyboard * getKeyboardListener();
	// �����¼��ָ�
	static void resumeEventListener();
	// ģ̬���ں���
	void playAgain(Ref *ref);
	void endGame(Ref * ref);

	void update(float f);

protected:
	static Adventure * adventure;
	Size visibleSize;
	int reach_count = 0;
	Sprite* player = NULL;
	

	StatusLayer *  statusLayer;

	int life = 70;
	//int life = 10000;
	int level = 0;
	int attack = 10;
	int experience = 0;
	bool whether_black_hole = false;
	EventListenerKeyboard * keyboardListener;

	bool isRandom = false;
	bool isFirstRandom = false;
};

#endif
