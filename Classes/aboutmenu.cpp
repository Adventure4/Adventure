#include "aboutmenu.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

aboutmenu::aboutmenu() : m_world(NULL)
{

}

aboutmenu::~aboutmenu()
{

}

Scene* aboutmenu::creatScene()
{
	Scene* scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setGravity(Point(0, 0));
	auto layer = aboutmenu::create(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}

aboutmenu* aboutmenu::create(PhysicsWorld* world)
{
	aboutmenu* pRet = new aboutmenu();
	if (pRet && pRet->init(world))
	{
		return pRet;
	}
	pRet = NULL;
	return NULL;
}

bool aboutmenu::init(PhysicsWorld* world)
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("In the year of 2500, the earth is surrounded by Santi Anamy.\n"
		"The enemy are so powerful that human faced with a destroyed fate.\n"
		" You are a warrior that human has selected to find a new planet.\n"
		"You should beat the monsters and go through the wormstone in order to go farther.\n\n"
		"Don't be afraid.\n","fonts/comic.ttf" , 20);
	label->setPosition(Vec2(origin.x + visibleSize.width / 3+200,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	bgsprite = Sprite::create("background4.jpg");
	bgsprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bgsprite, 0);

	auto item3 = MenuItemLabel::create(Label::createWithTTF("Good luck!", "fonts/Marker Felt.ttf", 35), CC_CALLBACK_1(aboutmenu::Exit, this));

	auto menu = Menu::create(item3, NULL);
	menu->setPosition(Director::getInstance()->getVisibleSize().width / 5, Director::getInstance()->getVisibleSize().height / 3);
	menu->alignItemsVerticallyWithPadding(label->getContentSize().height / 3);
	this->addChild(menu, 2);

	return true;
}

void aboutmenu::Exit(Ref *ref)
{
	CCParticleSystem *p1 = CCParticleGalaxy::create();
	
	p1->setTexture(CCTextureCache::sharedTextureCache()->addImage("defend.png"));
	p1->setAutoRemoveOnFinish(true);
	p1->setPositionType(kCCPositionTypeFree);

	p1->setPosition(ccp(Director::getInstance()->getVisibleSize().width / 5, Director::getInstance()->getVisibleSize().height / 3));
	
	this->addChild(p1);

	this->schedule(schedule_selector(aboutmenu::backToMenu), 3);
}

void aboutmenu::backToMenu(float f)
{
	auto scene = Scene::create();
	auto *layer = MainMenu::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}