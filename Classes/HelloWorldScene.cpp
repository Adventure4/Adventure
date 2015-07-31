#include "HelloWorldScene.h"
#include "Slide.h"
#include "aboutmenu.h"
#include "Adventure.h"

#pragma execution_character_set("utf-8") 
USING_NS_CC;

const int FONT_SIZE = 45;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	totalTime = 0;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
	auto item1 = MenuItemLabel::create(Label::createWithTTF("Play\n", "fonts/comic.ttf", 35), CC_CALLBACK_1(HelloWorld::PlayMenu, this));
	auto item2 = MenuItemLabel::create(Label::createWithTTF("Background\n", "fonts/comic.ttf", 35), CC_CALLBACK_1(HelloWorld::About, this));
	auto item3 = MenuItemLabel::create(Label::createWithTTF("Exit\n", "fonts/comic.ttf", 35), CC_CALLBACK_1(HelloWorld::Exit, this));

	item1->setColor(Color3B(249, 180, 76));
	item2->setColor(Color3B(249, 180, 76));
	item3->setColor(Color3B(249, 180, 76));

	// create menu, it's an autorelease object
	auto menu = Menu::create(item1, item2, item3, NULL);
	menu->setPosition(Director::getInstance()->getVisibleSize().width / 4, Director::getInstance()->getVisibleSize().height / 2);
	menu->alignItemsVerticallyWithPadding(FONT_SIZE/2);
	this->addChild(menu, 2);

	CCParticleSystem *p1 = CCParticleSun ::create();

	//p1->setTexture(CCTextureCache::sharedTextureCache()->addImage("defend.png"));
	p1->setAutoRemoveOnFinish(true);
	p1->setPositionType(kCCPositionTypeRelative);
	p1->setTotalParticles(100);


	p1->setPosition(ccp(60, Director::getInstance()->getVisibleSize().height - 113));

	this->addChild(p1,3);

    // add bg
	auto bgsprite = Sprite::create("background5.jpg");
	float odds;
	float oddsY;
	oddsY = bgsprite->getContentSize().height / visibleSize.height;
	odds = bgsprite->getContentSize().width / visibleSize.width;
	bgsprite->setScaleY(1 / oddsY);
	bgsprite->setScaleX(1 / odds);
	bgsprite->setPosition(Vec2(visibleSize / 2) + origin);
	this->addChild(bgsprite, 0);

	//
	//
    return true;
}

void HelloWorld::PlayMenu(Ref *ref){
	//Scene * scene = Slide::createScene();
	//Director::getInstance()->pushScene(scene);
	Scene * scene = Adventure::scene();
	
	CCTransitionScene * reScene = NULL;

	float t = 1.2f;

	//    CCTransitionJumpZoom
	//    作用： 创建一个跳动的过渡动画
	//    参数1：过渡动作的时间
	//    参数2：切换到目标场景的对象
	reScene = CCTransitionFadeTR::create(t, scene);
	CCDirector::sharedDirector()->replaceScene(reScene);
}

void HelloWorld::About(Ref *ref){

	Scene * scene = aboutmenu::creatScene();
	//Director::getInstance()->pushScene(scene);

	CCTransitionScene * reScene = NULL;

	float t = 1.2f;

	//    CCTransitionJumpZoom
	//    作用： 创建一个跳动的过渡动画
	//    参数1：过渡动作的时间
	//    参数2：切换到目标场景的对象
	reScene = CCTransitionCrossFade::create(t, scene);
	CCDirector::sharedDirector()->replaceScene(reScene);

}

void HelloWorld::Exit(Ref *ref){
	//schedule(schedule_selector(HelloWorld::updateTime), 0.1f);
	//Adventure::resumeEventListener();
	Director::getInstance()->end();
}

void HelloWorld::updateTime(float dt){
	totalTime += dt;
	char t[10];
	sprintf(t, "%.1f", totalTime);
	timerStr->setString(t);
}