#include "Adventure1.h"


const float SIZE_WSAD = 100.0;
const int FONT_SIZE = 45;
const int NUM_BLACK_HOLE = 7;

const int HERO1_LIFE = 60;
const int HERO1_ATTACK = 5;
const int HERO1_EXP = 60;

const int HERO2_LIFE = 70;
const int HERO2_ATTACK = 10;
const int HERO2_EXP = 70;

const int HERO3_LIFE = 80;
const int HERO3_ATTACK = 15;
const int HERO3_EXP = 80;

const int HERO4_LIFE = 90;
const int HERO4_ATTACK = 20;
const int HERO4_EXP = 90;

const int HERO5_LIFE = 100;
const int HERO5_ATTACK = 25;
const int HERO5_EXP = 100;

const int HERO6_LIFE = 110;
const int HERO6_ATTACK = 30;
const int HERO6_EXP = 110;

const int expArray[10] = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500};
const int attackArray[10] = {10, 15, 20, 25, 30, 35, 40, 45, 50, 55};
const int lifeArray[10] = { 50, 70, 90, 110, 130, 150, 180, 220, 250, 300};


// 最初生命值为50，攻击力为10（数值可以改），经验值为0

Scene* Adventure1::createScene()
{
	auto scene = Scene::create();
	auto *layer = Adventure1::create();
	scene->addChild(layer);

	return scene;
}

Adventure1::Adventure1() {
	/*life = Adventure::getLife;
	level = Adventure::level;
	attack = Adventure::attack;
	experience = Adventure::experience;*/
}

// 实现移动的函数。每次移动时事件触发的判断可以加在这里。
void Adventure1::move(Point direct) {
	//bool flag = true;
	Point curPos = player->getPosition();
	Point nextPos = curPos + direct;

	// 不是三体围墙就可以移动
	Vector<Sprite*>::iterator it = v_wall.begin();
	for (; it != v_wall.end(); it++) {
		if ((*it)->getPosition() == nextPos)
			//flag = false;
			return;
	}

	judge("v_hero1", nextPos);
	judge("v_hero2", nextPos);
	judge("v_hero3", nextPos);
	judge("v_hero4", nextPos);
	judge("v_hero5", nextPos);
	judge("v_hero6", nextPos);
	judge("v_black_hole", nextPos);
	judge("v_destination", nextPos);
	judge("v_random", nextPos);
	judge("v_supply", nextPos);

	int x = player->getPosition().x;
	int y = player->getPosition().y;
	label_life->setString((String::createWithFormat("Health Value : \n   %d", life)->getCString()));
	//label_life->setString((String::createWithFormat("X = %d, Y = %d", x, y)->getCString()));
	label_attack->setString((String::createWithFormat("Attack Value:\n   %d", attack)->getCString()));
	label_level->setString((String::createWithFormat("Level:\n   %d", level)->getCString()));
	label_exp->setString((String::createWithFormat("Experience:\n   %d", experience)->getCString()));

	// 移动到下一位置
	if (whether_black_hole == true) {
		whether_black_hole = false;
		return;
	}
	//if (flag == true)
	player->setPosition(nextPos);
}

void Adventure1::judge(string obj, Point nextPos) {
	if (obj == "v_hero1") {
		Vector<Sprite*>::iterator it1 = v_hero1.begin();
		for (; it1 != v_hero1.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				label_info->setString((String::createWithFormat("A small monster\n")->getCString()));
				fightJudge((*it1), 1);
				it1 = v_hero1.erase(it1);
				break;
			}
	}
	if (obj == "v_hero2") {
		Vector<Sprite*>::iterator it1 = v_hero2.begin();
		for (; it1 != v_hero2.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				label_info->setString((String::createWithFormat("A small monster\n")->getCString()));
				fightJudge((*it1), 2);
				it1 = v_hero2.erase(it1);
				break;
			}
	}
	if (obj == "v_hero3") {
		Vector<Sprite*>::iterator it1 = v_hero3.begin();
		for (; it1 != v_hero3.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				label_info->setString((String::createWithFormat("A small monster\n")->getCString()));
				fightJudge((*it1), 3);
				it1 = v_hero3.erase(it1);
				break;
			}
	}
	if (obj == "v_hero4") {
		Vector<Sprite*>::iterator it1 = v_hero4.begin();
		for (; it1 != v_hero4.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				label_info->setString((String::createWithFormat("A small monster\n")->getCString()));
				fightJudge((*it1), 4);
				it1 = v_hero4.erase(it1);
				break;
			}
	}
	if (obj == "v_hero5") {
		Vector<Sprite*>::iterator it1 = v_hero5.begin();
		for (; it1 != v_hero5.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				label_info->setString((String::createWithFormat("A small monster\n")->getCString()));
				fightJudge((*it1), 5);
				it1 = v_hero5.erase(it1);
				break;
			}
	}
	if (obj == "v_hero6") {
		Vector<Sprite*>::iterator it1 = v_hero6.begin();
		for (; it1 != v_hero6.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				label_info->setString((String::createWithFormat("A small monster\n")->getCString()));
				fightJudge((*it1), 6);
				it1 = v_hero6.erase(it1);
				break;
			}
	}
	
	// 判断补给，恢复满血
	if (obj == "v_supply") {
		Vector<Sprite*>::iterator it = v_supply.begin();
		for (; it != v_supply.end(); it++)
			if ((*it)->getPosition() == nextPos) {
				label_info->setString((String::createWithFormat("A space station")->getCString()));
				life = lifeArray[level];
				(*it)->removeFromParentAndCleanup(true);
				it = v_supply.erase(it);
				break;
			}
	}

	// 判断黑洞，跳转场景
	if (obj == "v_black_hole") {
		Vector<Sprite*>::iterator it = v_black_hole.begin();
		for (; it != v_black_hole.end(); it++)
			if ((*it)->getPosition() == nextPos) {
				label_info->setString((String::createWithFormat("A black hole")->getCString()));
				BlackHole(nextPos, 0);
				// it = v_black_hole.erase(it);
				break;
			}
	}

	// 判断随机事件
	if (obj == "v_random") {
		Vector<Sprite*>::iterator it = v_random.begin();
		for (; it != v_random.end(); it++)
			if ((*it)->getPosition() == nextPos) {
				JumpRandom(nextPos);
				(*it)->removeFromParentAndCleanup(true);
				it = v_random.erase(it);
				break;
			}
	}

	// 到达虫洞终点
	if (obj == "v_destination") {
		Vector<Sprite*>::iterator it = v_destination.begin();
		for (; it != v_destination.end(); it++)
			if ((*it)->getPosition() == nextPos) {
				ShowWin();
				// it = v_destination.erase(it);
				break;
			}
	}
}


void Adventure1::BlackHole(Point nextPos, int version) {
	
	// 实现场景跳转
	Scene * scene = Slide::createScene();
	TransitionJumpZoom * tjz = TransitionJumpZoom::create(1, scene);
	Director::getInstance()->pushScene(tjz);

	whether_black_hole = true;
	int j, i, player_id;
	i = rand() % (NUM_BLACK_HOLE-1);
	if (version == 0) {
		Vector<Sprite*>::iterator it = v_black_hole.begin();
		for (j = 0; it != v_black_hole.end(); it++, j++)
			if ((*it)->getPosition() == nextPos) {
				player_id = j;
				break;
			}
	for (j = 0, it = v_black_hole.begin(); it != v_black_hole.end(); it++, j++)
		if (j == ((player_id + 1 + i) % NUM_BLACK_HOLE)) {
			Point p = (*it)->getPosition();
			player->setPosition(p);
			experience += 50;
			levelJudge();
			break;
		}
	}
	else {
		Vector<Sprite*>::iterator it = v_black_hole.begin();
		for (j = 0, it = v_black_hole.begin(); it != v_black_hole.end(); it++, j++)
			if (j == i){
			Point p = (*it)->getPosition();
			player->setPosition(p);
			experience += 50;
			levelJudge();
			break;
		}
	}
}

	// 以下随机事件均可弹窗显示
void Adventure1::JumpRandom(Point nextPos) {
	int i = rand() % 3;
	if (i == 0) {
		// 内部成员背叛，血量减少60
		label_info->setString((String::createWithFormat("Internal betray!")->getCString()));
		life -= 60;
		if (life <= 0)
			GameOver();
	}
	else if (i == 1) {
		// 拾获太空水晶，攻击力增加5
		label_info->setString((String::createWithFormat("Increase attack ability")->getCString()));
		attack += 5;
	}
	else if (i == 2) {
		// 遭遇黑洞，进入另一场景
		label_info->setString((String::createWithFormat("A black hole")->getCString()));
		BlackHole(nextPos, 1);

	}
}

void Adventure1::levelJudge() {
	if (experience >= expArray[level]) {
		experience -= expArray[level];
		level++;
		attack = attackArray[level];
		life = lifeArray[level];
	}
}

void Adventure1::fightJudge(Sprite* it_sprite, int num) {
	int _life, _attack;
	if (num == 1) {
		_life = HERO1_LIFE;
		_attack = HERO1_ATTACK;
	}
	else if (num == 2) {
		_life = HERO2_LIFE;
		_attack = HERO2_ATTACK;
	}
	else if (num == 3){
		_life = HERO3_LIFE;
		_attack = HERO3_ATTACK;
	}
	else if (num == 4){
		_life = HERO4_LIFE;
		_attack = HERO4_ATTACK;
	}
	else if (num == 5){
		_life = HERO5_LIFE;
		_attack = HERO5_ATTACK;
	}
	else if (num == 6){
		_life = HERO6_LIFE;
		_attack = HERO6_ATTACK;
	}
	while (life > 0 && _life > 0) {
		life -= _attack;
		_life -= attack;
	}
	if (life <= 0)
		GameOver();
	else if (_life <= 0) {
		experience += HERO1_EXP;
		levelJudge();
		it_sprite->removeFromParentAndCleanup(true);
	}
}


// 从tilemap中导入对象
Vector <Sprite *> Adventure1::loadFromMap(TMXTiledMap* tmx, string obj, string name, int DisX, int DisY) {
	//从tmx中获取对象层
	TMXObjectGroup* object = tmx->getObjectGroup(obj);
	//从对象层中获取对象数组
	ValueVector container = object->getObjects();
	//遍历对象
	Vector<Sprite *> v;
	int x, y;
	for (auto obj : container){
		ValueMap values = obj.asValueMap();
		//获取纵横轴坐标（cocos2dx坐标）
		x = values.at("x").asInt();
		y = values.at("y").asInt();
		Sprite* temp = Sprite::create(name);
		v.pushBack(temp);
		temp->setAnchorPoint(Vec2(0, 0));
		temp->setPosition(Point(x + DisX, y + DisY));
		this->addChild(temp, 1);
	}
	return v;
}

Scene* Adventure1::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto *layer = Adventure1::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

/*
Adventure1::Adventure1()
{
	
}
*/

Adventure1::~Adventure1()
{

}

bool Adventure1::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	// 背景图片可以换
	Sprite* background = Sprite::create("background2.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	
	dispatcher = Director::getInstance()->getEventDispatcher();
	KeyboardEvent();
	
	loadObject();
	
	return true;
}





void Adventure1::KeyboardEvent()
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Adventure1::onKeyPressed, this);
	//listener->onKeyReleased = CC_CALLBACK_2(Adventure::onKeyReleased, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Adventure1::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
	switch (code)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		onLeftPressed(this);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		onRightPressed(this);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		onUpPressed(this);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		onDownPressed(this);
		break;
	default:
		break;
	}
}

void Adventure1::loadObject(){
	//根据文件路径快速导入瓦片地图
	TMXTiledMap* tmx = TMXTiledMap::create("map1.tmx");
	//设置位置
	tmx->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//设置锚点
	tmx->setAnchorPoint(Vec2(0.5, 0.5));
	int DisX = (visibleSize.width - tmx->getContentSize().width) / 2 - 64 * 5;
	int DisY = (visibleSize.height - tmx->getContentSize().height) / 2 - 64 * 4;
	//添加到游戏图层中，其中0代表Z轴（Z轴低的会被高的遮挡）
	this->addChild(tmx, 0);

	//从tmx中获取对象层player
	TMXObjectGroup* object3 = tmx->getObjectGroup("player");
	//从对象层中获取对象数组
	ValueVector container3 = object3->getObjects();
	//遍历对象
	int x, y;
	for (auto obj : container3){
		ValueMap values = obj.asValueMap();
		//获取纵横轴坐标（cocos2dx坐标）
		x = values.at("x").asInt();
		y = values.at("y").asInt();
		Sprite* temp = Sprite::create("alient.png");
		temp->setAnchorPoint(Vec2(0, 0));
		temp->setPosition(Point(x + DisX, y + DisY));
		player = temp;
		this->addChild(temp, 5);
	}

	// 导入对象后存入对应的vector中
	v_wall = loadFromMap(tmx, "wall", "wall.png", DisX, DisY);
	v_hero1 = loadFromMap(tmx, "blackwidow", "6.png", DisX, DisY);
	v_hero2 = loadFromMap(tmx, "eagleeye", "5.png", DisX, DisY);
	v_hero3 = loadFromMap(tmx, "captain", "4.png", DisX, DisY);
	v_hero4 = loadFromMap(tmx, "ironman", "3.png", DisX, DisY);
	v_hero5 = loadFromMap(tmx, "hulk", "2.png", DisX, DisY);
	v_hero6 = loadFromMap(tmx, "thor", "1.png", DisX, DisY);
	v_black_hole = loadFromMap(tmx, "black_hole", "black_hole.jpg", DisX, DisY);
	v_destination = loadFromMap(tmx, "worm_hole", "worm_stone.png", DisX, DisY);
	v_random = loadFromMap(tmx, "random", "random.jpg", DisX, DisY);
	v_supply = loadFromMap(tmx, "supply", "supply_space.jpg", DisX, DisY);
	
	label_info = Label::createWithTTF((String::createWithFormat("Warrior, forward to\nthe unknown.")->getCString()),
		"fonts/Marker Felt.ttf", 20);
	label_info->setPosition(visibleSize.width / 2 - 400, visibleSize.height / 2 + 120);
	this->addChild(label_info, 4);

	label_life = Label::createWithTTF((String::createWithFormat("Health Value:\n   %d", life)->getCString()),
		"fonts/Marker Felt.ttf", 20);
	label_life->setPosition(visibleSize.width / 2 - 400, visibleSize.height / 2 + 60);
	this->addChild(label_life, 4);

	label_attack = Label::createWithTTF((String::createWithFormat("Attack Value:\n   %d", attack)->getCString()),
		"fonts/Marker Felt.ttf", 20);
	label_attack->setPosition(visibleSize.width / 2 - 400, visibleSize.height / 2);
	this->addChild(label_attack, 4);

	label_level = Label::createWithTTF((String::createWithFormat("Level:\n   %d", level)->getCString()),
		"fonts/Marker Felt.ttf", 20);
	label_level->setPosition(visibleSize.width / 2 - 420, visibleSize.height / 2 - 60);
	this->addChild(label_level, 4);

	label_exp = Label::createWithTTF((String::createWithFormat("Experience:\n   %d", experience)->getCString()),
		"fonts/Marker Felt.ttf", 20);
	label_exp->setPosition(visibleSize.width / 2 - 400, visibleSize.height / 2 - 120);
	this->addChild(label_exp, 4);
}

void Adventure1::onRightPressed(Ref* sender)
{
	// 按下按键d的事件实现
	// 判断是否可走(有墙时不能走)
	Point direct = Vec2(64, 0);
	move(direct);
}

void Adventure1::onLeftPressed(Ref* sender)
{
	// 按下按键a的事件实现
	// 判断是否可走(有墙时不能走)
	Point direct = Vec2(-64, 0);
	move(direct);
}

void Adventure1::onUpPressed(Ref* sender)
{
	//按下按键w的事件实现
	// 判断是否可走(有墙时不能走)
	Point direct = Vec2(0, 64);
	move(direct);
}

void Adventure1::onDownPressed(Ref* sender)
{
	//按下按键s的事件实现
	// 判断是否可走(有墙时不能走)
	Point direct = Vec2(0, -64);
	move(direct);
}

void Adventure1::Restart(Ref* sender) {

	auto scene = Scene::create();
	auto *layer = Adventure1::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}

void Adventure1::ShowWin() {
	// 简单存取

	/*if (count < database->getIntegerForKey("min_step") || database->getIntegerForKey("min_step")== 0)
		database->setIntegerForKey("min_step", count);
	label_life->setString((String::createWithFormat("Current step:\n   %d", count)->getCString()));

	auto label_win = Label::createWithTTF("You win!", "fonts/Marker Felt.ttf", FONT_SIZE);

	label_win->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	this->addChild(label_win,4);*/
}

void Adventure1::GameOver() {
	// 弹出失败对话框，可以选择重新开始

}