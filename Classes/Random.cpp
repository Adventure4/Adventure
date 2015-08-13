#include "Random.h"
#include "Adventure.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Random * Random::random = NULL;

Random::Random()
{

}

Random::~Random()
{

}

Scene* Random::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	Random::random = Random::create();

	// add layer as a child to scene
	scene->addChild(Random::random);

	// return the scene
	return scene;
}

bool Random::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	auto bgsprite = Sprite::create("sky2.jpg");
	float odds;
	float oddsY;
	oddsY = bgsprite->getContentSize().height / visibleSize.height;
	odds = bgsprite->getContentSize().width / visibleSize.width;
	bgsprite->setScaleY(1 / oddsY);
	bgsprite->setScaleX(1 / odds);
	bgsprite->setPosition(Vec2(visibleSize / 2));
	this->addChild(bgsprite, 0);

	auto item1 = Sprite::create("chest_2.png");
	auto item2 = Sprite::create("chest_2.png");
	auto item3 = Sprite::create("chest_2.png");
	item1->setPosition(visibleSize.width / 2, 450);
	item2->setPosition(visibleSize.width / 4, 450);
	item3->setPosition(visibleSize.width / 4 * 3, 450);
	this->addChild(item1, 1);
	this->addChild(item2, 1);
	this->addChild(item3, 1);

	auto button1 = MenuItemLabel::create(Label::createWithTTF("SELECT\n", "fonts/comici.ttf", 30), CC_CALLBACK_1(Random::select, this));
	button1->setPosition(visibleSize.width / 2, 350);
	auto button2 = MenuItemLabel::create(Label::createWithTTF("SELECT\n", "fonts/comici.ttf", 30), CC_CALLBACK_1(Random::select, this));
	button2->setPosition(visibleSize.width / 4, 350);
	auto button3 = MenuItemLabel::create(Label::createWithTTF("SELECT\n", "fonts/comici.ttf", 30), CC_CALLBACK_1(Random::select, this));
	button3->setPosition(visibleSize.width / 4 * 3, 350);
	button1->setColor(Color3B::BLACK);
	button2->setColor(Color3B::BLACK);
	button3->setColor(Color3B::BLACK);
	Menu* menu = Menu::create(button1, button2, button3, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu, 1);
	return true;
}

void Random::select(Ref *ref)
{

	auto thor = Sprite::create("thor_.png");
	auto conver = Sprite::create("conver.png");
	thor->setPosition(visibleSize.width / 6 * 5, 100);
	conver->setPosition(visibleSize.width / 2 + 130, 230);
	this->addChild(thor, 1);
	this->addChild(conver, 1);
	 
	auto label = Label::createWithTTF("", "fonts/comic.ttf", 24);
	label->setColor(Color3B::BLACK);
	label->setPosition(visibleSize.width / 2 + 130, 245);
	this->addChild(label, 2);

	Global * global = Global::getInstance();
	int life = global->getLife();
	int attack = global->getAttack();
	int experience = global->getExperience();

	//life -= 60;

	int i = rand() % 3;
	if (i == 0) {
		// 内部成员背叛，血量减少60
		life -= 60;
		global->setLife(life);
		label->setString("  Oops!Your health\n    value decreases\n          by 60!");
	}
	else if (i == 1) {
		// 拾获太空水晶，攻击力增加5
		attack += 5;
		global->setAttack(attack);
		label->setString("  Hey,man!Your\n   attack value\n     increase\n        by 5!");
	}
	else if (i == 2) {
		// 经验值加20
		experience += 20;
		global->setExperience(experience);
		label->setString("     Wow,your\n experience value\n increase by 20!");
	}
	schedule(schedule_selector(Random::time), 3);
	
}
void Random::time(float dt){
	Director::getInstance()->popScene();
}