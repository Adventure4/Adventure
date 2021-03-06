#include "Adventure.h"
#include "Adventure1.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

const float SIZE_WSAD = 100.0;
const int FONT_SIZE = 45;
const int NUM_BLACK_HOLE = 7;

const int heroLife[6] = {60, 70, 80, 90, 100, 110};
const int heroAttack[6] = {5, 10, 15, 20, 25, 30};
const int heroExp[6] = { 60, 70, 80, 90, 100, 110 };

// add
const float MOVE_TIME = 0.3f;
const int expArray[10] = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500};
const int attackArray[10] = {10, 15, 20, 25, 30, 35, 40, 45, 50, 55};
//const int lifeArray[10] = { 60, 70, 90, 110, 130, 150, 180, 220, 250, 300};
const int lifeArray[10] = {70, 80, 90, 100, 110, 120, 130, 140, 150, 160};

Adventure * Adventure::adventure = NULL;

// 实现移动的函数。每次移动时事件触发的判断可以加在这里。
void Adventure::move(Point direct) {
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

	if (isRandom) {
		isRandom = false;
		isFirstRandom = true;
		schedule(schedule_selector(Adventure::update), 0.2f);
	}
	else {
		unschedule(schedule_selector(Adventure::update));
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
	SimpleAudioEngine::getInstance()->playEffect("music/player_move.wav");
	player->setPosition(nextPos);
}

void Adventure::update(float f)
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

void Adventure::judge(string obj, Point nextPos) {
	
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
	if (obj == "v_destination") {
		Vector<Sprite*>::iterator it = v_destination.begin();
		for (; it != v_destination.end(); it++)
			if ((*it)->getPosition() == nextPos) {
				NextMap();
				// it = v_destination.erase(it);
				break;
			}
	}
}

void Adventure::BlackHole(Point nextPos, int version) {
	
	// 实现场景跳转
	Scene * scene = Slide::createScene();/*
	TransitionJumpZoom * tjz = TransitionJumpZoom::create(1, scene);*/
	//Director::getInstance()->pushScene(tjz);
	Director::getInstance()->pushScene(Util::getTransitionSceneRandom(scene));
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
void Adventure::JumpRandom(Point nextPos) {
	Global * global = Global::getInstance();
	global->setLife(life);
	global->setLevel(level);
	global->setExperience(experience);
	global->setAttack(attack);

	Scene * scene = Random::scene();
	Director::getInstance()->pushScene(scene);
}

void Adventure::levelJudge() {
	if (experience >= expArray[level]) {
		experience -= expArray[level];
		int remain = attack - attackArray[level];
		level++;
		attack = attackArray[level] + remain;
		life = lifeArray[level];
	}
}

void Adventure::fightJudge(Sprite* it_sprite, int num) {
	int _life, _attack;
	_life = heroLife[num-1];
	_attack = heroAttack[num-1];
	
	while (life > 0 && _life > 0) {
		life -= _attack;
		_life -= attack;
	}
	if (life <= 0)
		GameOver();
	else if (_life <= 0) {
		experience += heroExp[num - 1];
		String *str = String::createWithFormat("Get %d experience...", heroExp[num-1]);
		WarLayer::showWarWindow(this, "W I N", *str);
		levelJudge();
		it_sprite->removeFromParentAndCleanup(true);
	}
}


// 从tilemap中导入对象
Vector <Sprite *> Adventure::loadFromMap(TMXTiledMap* tmx, string obj, string name, int DisX, int DisY) {
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

Scene* Adventure::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	Adventure::adventure = Adventure::create();
	
	// add layer as a child to scene
	scene->addChild(Adventure::adventure);

	// return the scene
	return scene;
}

Adventure::Adventure()
{
	
}

Adventure::~Adventure()
{

}

bool Adventure::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	auto bgsprite = Sprite::create("bg1.jpg");
	float odds;
	float oddsY;
	oddsY = bgsprite->getContentSize().height / visibleSize.height;
	odds = bgsprite->getContentSize().width / visibleSize.width;
	bgsprite->setScaleY(1 / oddsY);
	bgsprite->setScaleX(1 / odds);
	bgsprite->setPosition(Vec2(visibleSize / 2));
	this->addChild(bgsprite, 0);
	
	loadObject();

	// 键盘事件
	addKeyboardEvent();
	
	// 添加银河背景 添加.plist时记得保证有textureFileName或textureImageData标签，添加了就要设置，且值不能为空
	auto galaxy = ParticleSystemQuad::create("Galaxy.plist");
	galaxy->setPosition(visibleSize / 2);
	this->addChild(galaxy, 0);

	// 添加背景音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/map_music0.mp3", true);

	return true;
}

void Adventure::loadObject(){
	//根据文件路径快速导入瓦片地图
	TMXTiledMap* tmx = TMXTiledMap::create("map.tmx");
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

	// 显示生命值/攻击力/经验值的图像
	Sprite* label_life = Sprite::create("label_life.png");
	label_life->setPosition(55, 64*5 + 5);
	addChild(label_life, 7);
	Sprite* label_attack = Sprite::create("label_attack.png");
	label_attack->setPosition(55, 64 * 4 + 15) ;
	addChild(label_attack, 7);
	Sprite* label_level = Sprite::create("label_level.png");
	label_level->setPosition(55, 64 * 3 + 33);
	addChild(label_level, 7);
	Sprite* label_exp = Sprite::create("label_exp.png");
	label_exp->setPosition(55, 64 * 2 + 45);
	addChild(label_exp, 7);
	

	// 导入对象后存入对应的vector中
	v_wall = loadFromMap(tmx, "wall", "floor.png", DisX, DisY);
	v_hero1 = loadFromMap(tmx, "blackwidow", "6.png", DisX, DisY);
	v_hero2 = loadFromMap(tmx, "eagleeye", "5.png", DisX, DisY);
	v_hero3 = loadFromMap(tmx, "captain", "4.png", DisX, DisY);
	v_hero4 = loadFromMap(tmx, "ironman", "3.png", DisX, DisY);
	v_hero5 = loadFromMap(tmx, "hulk", "2.png", DisX, DisY);
	v_hero6 = loadFromMap(tmx, "thor", "1.png", DisX, DisY);
	//v_monster3 = loadFromMap(tmx, "monster3", "monster3.png", DisX, DisY);
	v_black_hole = loadFromMap(tmx, "black_hole", "black_hole.png", DisX, DisY);
	v_destination = loadFromMap(tmx, "worm_hole", "worm_stone.png", DisX, DisY);
	v_random = loadFromMap(tmx, "random", "random.png", DisX, DisY);
	v_supply = loadFromMap(tmx, "supply", "supply_space.png", DisX, DisY);

	statusLayer = StatusLayer::createLayer();
	statusLayer->setLabelInfo("hello");
	statusLayer->setLabelLevel(level);
	statusLayer->setLabelAttack(attack);
	statusLayer->setLabelExp(experience,level);
	statusLayer->setLabelLife(life, level);
	statusLayer->setContentSize(Size(300, 300));
	statusLayer->setBackground("layers/InfoLayer.png");
	statusLayer->setCascadeOpacityEnabled(true);
	statusLayer->setOpacity(255 * 0.6);
	//statusLayer->setOpacity(255*0.8);
	statusLayer->setPosition(statusLayer->getContentSize().width / 2, visibleSize.height / 2);
	this->addChild(statusLayer, 5);



}

void Adventure::onRightPressed(Ref* sender)
{
	// 按下按键d的事件实现
	// 判断是否可走(有墙时不能走)
	Point direct = Vec2(64, 0);
	move(direct);
}

void Adventure::onLeftPressed(Ref* sender)
{
	// 按下按键a的事件实现
	// 判断是否可走(有墙时不能走)
	Point direct = Vec2(-64, 0);
	move(direct);
}

void Adventure::onUpPressed(Ref* sender)
{
	//按下按键w的事件实现
	// 判断是否可走(有墙时不能走)
	Point direct = Vec2(0, 64);
	move(direct);
}

void Adventure::onDownPressed(Ref* sender)
{
	//按下按键s的事件实现
	// 判断是否可走(有墙时不能走)
	Point direct = Vec2(0, -64);
	move(direct);
}

void Adventure::Restart(Ref* sender) {

	auto scene = Scene::create();
	auto *layer = Adventure::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}

void Adventure::NextMap() {
	
	// 暂存各项属性值
	Global * global = Global::getInstance();
	global->setLife(life);
	global->setLevel(level);
	global->setExperience(experience);
	global->setAttack(attack);
	// 简单存取
	// 实现场景跳转
	Scene * scene = Adventure1::createScene();
	//TransitionJumpZoom * tjz = TransitionJumpZoom::create(1, scene);
	TransitionShrinkGrow *tsg = TransitionShrinkGrow::create(1.0f, scene);
	//Director::getInstance()->pushScene(tsg);
	Director::getInstance()->replaceScene(tsg);
	/*Director::getInstance()->pushScene(tjz);*/
}

void Adventure::GameOver() {
	// 弹出失败对话框，可以选择重新开始
	//WarLayer::showWarWindow(this, "L O S E", "Who can save the earth?...");
	//DialogLayer *dia = DialogLayer::create();
	//this->addChild(dia, 6);
	DialogLayer::showDialogLayer(this, "L O S E ! ! !", "Restart", menu_selector(Adventure::playAgain), "Quit", menu_selector(Adventure::endGame));
}

void Adventure::keyPressed(EventKeyboard::KeyCode keyCode, Event *event) {

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

void Adventure::keyRelease(EventKeyboard::KeyCode keyCode, Event *event) {

}

void Adventure::addKeyboardEvent() {
	keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Adventure::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Adventure::keyRelease, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Adventure::playAgain(Ref *ref) {
	Adventure::resumeEventListener();
	Scene * scene = Adventure::scene();
	Director::getInstance()->replaceScene(scene);
}

void Adventure::endGame(Ref * ref) {
	Adventure::resumeEventListener();
	Director::getInstance()->end();
}

void Adventure::resumeEventListener() {
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(Adventure::adventure);
}