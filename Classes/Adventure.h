#ifndef  ADVENTURE_H_
#define  ADVENTURE_H_

#include "cocos2d.h"
#include "Slide.h"
#include "Global.h"
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
	存储各个对象的vector，包括：
	wall：不可前进
	stone：陨石，可减少生命值
	monster1;怪物1
	monster2;怪物2
	black_hole;黑洞，可触发另一场景。胜利后随机出现在另一黑洞中
	destination;终点，虫洞标志。共有另个虫洞，一个被黑洞包围，另一个被高级怪物包围。
	random;随机事件
	supply;供给站
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

	void KeyboardEvent();
	void onKeyPressed(EventKeyboard::KeyCode code, Event* event);

	void loadObject();
	void info(float dt);

	// 将导入对象的操作封装起来的函数
	Vector <Sprite *> loadFromMap(TMXTiledMap* tmx, string obj, string name, int DisX, int DisY);

	//控制player移动的函数，其中内容封装在move()中
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
	void ShowWin();
	void GameOver();

	bool win;

protected:
	Size visibleSize;
	int reach_count = 0;
	Sprite* player = NULL;

	EventDispatcher* dispatcher;

	int life = 60;
	int level = 1;
	int attack = 10;
	int experience = 0;
	bool whether_black_hole = false;
	//bool is_info = false;

	Label* label_info;
	// 显示生命值和攻击力的标签
	Label* label_life;
	Label* label_attack;
	Label* label_level;
	Label* label_exp;
};

#endif
