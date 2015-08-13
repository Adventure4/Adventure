#include "Adventure1.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
static int num = 0;
static int lastLife = 0;
static int lastLevel = 0;
static int lastAttack = 0;
static int lastExp = 0;
const float SIZE_WSAD = 100.0;
const int FONT_SIZE = 45;
const int NUM_BLACK_HOLE = 7;
const int heroLife[6] = { 60, 70, 80, 90, 100, 110 };
const int heroAttack[6] = { 10, 15, 20, 25, 30, 35 };
const int heroExp[6] = { 60, 70, 80, 90, 100, 110 };
const int expArray[15] = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750};
const int attackArray[15] = {10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80};
//const int lifeArray[15] = { 60, 70, 90, 110, 130, 150, 180, 220, 250, 300, 330, 360, 490, 520, 550};
const int lifeArray[15] = { 70,80, 90, 100, 110, 120, 130, 140, 150, 160, 170 ,180, 190, 200, 210 };
//const int lifeArray[10] = { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000 };

Adventure1 * Adventure1::adventure = NULL;

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
	judge("v_random", nextPos);
	judge("v_supply", nextPos);
	judge("v_destination", nextPos);

	int x = player->getPosition().x;
	int y = player->getPosition().y;

	if (isRandom) {
		schedule(schedule_selector(Adventure1::update), 0.2f);
		isRandom = false;
		isFirstRandom = true;
	}
	else {
		unschedule(schedule_selector(Adventure1::update));
	}

	statusLayer->setLabelLevel(level);
	statusLayer->setLabelAttack(attack);
	statusLayer->setLabelExp(experience, level);
	statusLayer->setLabelLife(life, level);

	// 移动到下一位置
	if (whether_black_hole == true) {
		SimpleAudioEngine::getInstance()->playEffect("music/into_black_hole.wav");
		whether_black_hole = false;
		return;
	}
	//if (flag == true)
	SimpleAudioEngine::getInstance()->playEffect("music/player_move.wav");
	player->setPosition(nextPos);
}

void Adventure1::update(float f)
{
	if (isFirstRandom) {
		Global * global = Global::getInstance();
		life = global->getLife();
		attack = global->getAttack();
		experience = global->getExperience();

		levelJudge();
		statusLayer->setLabelLevel(level);
		statusLayer->setLabelAttack(attack);
		statusLayer->setLabelExp(experience, level);
		statusLayer->setLabelLife(life, level);

		isFirstRandom = false;
	}

	if (life <= 0) {
		GameOver();
		return;
	}
}

void Adventure1::judge(string obj, Point nextPos) {
	if (obj == "v_hero1") {
		Vector<Sprite*>::iterator it1 = v_hero1.begin();
		for (; it1 != v_hero1.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				SimpleAudioEngine::getInstance()->playEffect("music/fight1.wav");
				statusLayer->setLabelInfo("Black Widow");
				fightJudge((*it1), 1);
				it1 = v_hero1.erase(it1);
				break;
			}
	}
	if (obj == "v_hero2") {
		Vector<Sprite*>::iterator it1 = v_hero2.begin();
		for (; it1 != v_hero2.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				SimpleAudioEngine::getInstance()->playEffect("music/fight1.wav");
				statusLayer->setLabelInfo("Eagle Eye");
				fightJudge((*it1), 2);
				it1 = v_hero2.erase(it1);
				break;
			}
	}
	if (obj == "v_hero3") {
		Vector<Sprite*>::iterator it1 = v_hero3.begin();
		for (; it1 != v_hero3.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				SimpleAudioEngine::getInstance()->playEffect("music/fight2.wav");
				statusLayer->setLabelInfo("Captain America");
				fightJudge((*it1), 3);
				it1 = v_hero3.erase(it1);
				break;
			}
	}
	if (obj == "v_hero4") {
		Vector<Sprite*>::iterator it1 = v_hero4.begin();
		for (; it1 != v_hero4.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				SimpleAudioEngine::getInstance()->playEffect("music/fight2.wav");
				statusLayer->setLabelInfo("Ironman");
				fightJudge((*it1), 4);
				it1 = v_hero4.erase(it1);
				break;
			}
	}
	if (obj == "v_hero5") {
		Vector<Sprite*>::iterator it1 = v_hero5.begin();
		for (; it1 != v_hero5.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				SimpleAudioEngine::getInstance()->playEffect("music/fight3.wav");
				statusLayer->setLabelInfo("Hulk");
				fightJudge((*it1), 5);
				it1 = v_hero5.erase(it1);
				break;
			}
	}
	if (obj == "v_hero6") {
		Vector<Sprite*>::iterator it1 = v_hero6.begin();
		for (; it1 != v_hero6.end(); it1++)
			if ((*it1)->getPosition() == nextPos) {
				SimpleAudioEngine::getInstance()->playEffect("music/fight3.wav");
				statusLayer->setLabelInfo("Thor");
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
				SimpleAudioEngine::getInstance()->playEffect("music/cure.wav");
				statusLayer->setLabelInfo("A space station");
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
				statusLayer->setLabelInfo("A black hole");
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
				isRandom = true;
				SimpleAudioEngine::getInstance()->playEffect("music/random.wav");
				JumpRandom(nextPos);
				(*it)->removeFromParentAndCleanup(true);
				it = v_random.erase(it);
				break;
			}
	}

	// 到达虫洞终点
	if (obj == "v_destination")
		if (nextPos == goal->getPosition())
			ShowWin();

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
	Global * global = Global::getInstance();
	global->setLife(life);
	global->setLevel(level);
	global->setExperience(experience);
	global->setAttack(attack);

	Scene * scene = Random::scene();
	Director::getInstance()->pushScene(scene);
}

void Adventure1::levelJudge() {
	if (experience >= expArray[level]) {
		experience -= expArray[level];
		int remain = attack - attackArray[level];
		level++;
		attack = attackArray[level]+remain;
		life = lifeArray[level];
	}
}

void Adventure1::fightJudge(Sprite* it_sprite, int num) {
	int _life, _attack;
	_life = heroLife[num - 1];
	_attack = heroAttack[num - 1];
	
	while (life > 0 && _life > 0) {
		life -= _attack;
		_life -= attack;
	}
	if (life <= 0)
		GameOver();
	else if (_life <= 0) {
		experience += heroExp[num - 1];
		String *str = String::createWithFormat("Get %d experience...", heroExp[num - 1]);
		WarLayer::showWarWindow(this, "W I N", *str);			
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
	
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	Adventure1::adventure = Adventure1::create();

	// add layer as a child to scene
	scene->addChild(Adventure1::adventure);

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
	auto bgsprite = Sprite::create("bg5.jpg");
	float odds;
	float oddsY;
	oddsY = bgsprite->getContentSize().height / visibleSize.height;
	odds = bgsprite->getContentSize().width / visibleSize.width;
	bgsprite->setScaleY(1 / oddsY);
	bgsprite->setScaleX(1 / odds);
	bgsprite->setPosition(Vec2(visibleSize / 2));
	this->addChild(bgsprite, 0);

	if (num == 0){
		Global * global = Global::getInstance();
		life = global->getLife();
		attack = global->getAttack();
		experience = global->getExperience();
		level = global->getLevel();
		lastLife = life;
		lastAttack = attack;
		lastExp = experience;
		lastLevel = level;
	}
	else{
		life = lastLife;
		attack = lastAttack;
		experience = lastExp;
		level = lastLevel;
	}
	
	loadObject();

	// 键盘事件
	addKeyboardEvent();
	
	return true;
}



void Adventure1::loadObject(){
	//根据文件路径快速导入瓦片地图
	TMXTiledMap* tmx = TMXTiledMap::create("map1.tmx");
	//设置位置
	tmx->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//设置锚点
	tmx->setAnchorPoint(Vec2(0.5, 0.5));
	int DisX = (visibleSize.width - tmx->getContentSize().width) / 2 - 64 * 2.5;
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

	TMXObjectGroup* object2 = tmx->getObjectGroup("destination");
	//从对象层中获取对象数组
	ValueVector container2 = object2->getObjects();
	//遍历对象
	for (auto obj : container2){
		ValueMap values = obj.asValueMap();
		//获取纵横轴坐标（cocos2dx坐标）
		x = values.at("x").asInt();
		y = values.at("y").asInt();
		Sprite* temp = Sprite::create("goal.png");
		temp->setAnchorPoint(Vec2(0, 0));
		temp->setPosition(Point(x + DisX, y + DisY));
		goal = temp;
		this->addChild(temp, 1);
	}

	// 显示生命值/攻击力/经验值的图像
	Sprite* label_life = Sprite::create("label_life.png");
	label_life->setPosition(55, 64 * 6 - 10);
	addChild(label_life, 7);
	Sprite* label_attack = Sprite::create("label_attack.png");
	label_attack->setPosition(55, 64 * 5);
	addChild(label_attack, 7);
	Sprite* label_level = Sprite::create("label_level.png");
	label_level->setPosition(55, 64 * 4 + 18);
	addChild(label_level, 7);
	Sprite* label_exp = Sprite::create("label_exp.png");
	label_exp->setPosition(55, 64 * 3 + 30);
	addChild(label_exp, 7);

	// 导入对象后存入对应的vector中
	v_wall = loadFromMap(tmx, "wall", "floor.png", DisX, DisY);
	v_hero1 = loadFromMap(tmx, "blackwidow", "6.png", DisX, DisY);
	v_hero2 = loadFromMap(tmx, "eagleeye", "5.png", DisX, DisY);
	v_hero3 = loadFromMap(tmx, "captain", "4.png", DisX, DisY);
	v_hero4 = loadFromMap(tmx, "ironman", "3.png", DisX, DisY);
	v_hero5 = loadFromMap(tmx, "hulk", "2.png", DisX, DisY);
	v_hero6 = loadFromMap(tmx, "thor", "1.png", DisX, DisY);
	v_black_hole = loadFromMap(tmx, "black_hole", "black_hole.png", DisX, DisY);
	v_destination = loadFromMap(tmx, "worm_hole", "worm_stone.png", DisX, DisY);
	v_random = loadFromMap(tmx, "random", "random.png", DisX, DisY);
	v_supply = loadFromMap(tmx, "supply", "supply_space.png", DisX, DisY);
	
	statusLayer = StatusLayer::createLayer();
	statusLayer->setLabelInfo("hello");
	statusLayer->setLabelLevel(level);
	statusLayer->setLabelAttack(attack);
	statusLayer->setLabelExp(experience, level);
	statusLayer->setLabelLife(life, level);
	statusLayer->setOpacity(0.5);
	statusLayer->setContentSize(Size(300, 300));
	statusLayer->setBackground("layers/InfoLayer.png");
	statusLayer->setCascadeOpacityEnabled(true);
	statusLayer->setOpacity(255 * 0.6);
	statusLayer->setPosition(statusLayer->getContentSize().width / 2, visibleSize.height / 2);
	this->addChild(statusLayer, 5);
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
	// 弹出胜利对话框，可以选择重新开始
	DialogLayer::showDialogLayer(this, "THE END\nAlient, you occupy the earth!!", "Restart", menu_selector(Adventure1::playAgain1), "Quit", menu_selector(Adventure1::endGame), DialogLayer::STATUS::WIN);
}

void Adventure1::GameOver() {
	// 弹出失败对话框，可以选择重新开始
	DialogLayer::showDialogLayer(this, "L O S E ! ! !", "Restart", menu_selector(Adventure1::playAgain2), "Quit", menu_selector(Adventure1::endGame));
}

void Adventure1::keyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_CAPITAL_A || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		onLeftPressed(this);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D || keyCode == EventKeyboard::KeyCode::KEY_CAPITAL_D || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		onRightPressed(this);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_CAPITAL_W || keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		onUpPressed(this);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_CAPITAL_S || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		onDownPressed(this);
	}
}
void Adventure1::keyRelease(EventKeyboard::KeyCode keyCode, Event *event) {

}

void Adventure1::addKeyboardEvent() {
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Adventure1::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Adventure1::keyRelease, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

// 从第一关开始，用于游戏胜利后
void Adventure1::playAgain1(Ref *ref) {
	Scene * scene = Adventure::scene();
	Director::getInstance()->replaceScene(scene);
}

// 从第二关开始，用于游戏失败时
void Adventure1::playAgain2(Ref *ref) {
	num += 1;;
	unschedule(schedule_selector(Adventure1::update));
	Scene * scene = Adventure1::scene();
	Director::getInstance()->replaceScene(scene);
}

void Adventure1::endGame(Ref * ref) {
	Director::getInstance()->end();
}