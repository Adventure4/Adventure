#include "DialogLayer.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

DialogLayer::DialogLayer()
{
}

DialogLayer::~DialogLayer()
{
}

DialogLayer * DialogLayer::createLayer() {
	return DialogLayer::create();
}

bool DialogLayer::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)));
        
        this->initDialog();
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void DialogLayer::initDialog()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* bg = Sprite::create("dia.jpg");
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bg, 0);
    
    CCMenuItemFont *exitMenuItem = CCMenuItemFont::create("Quit", this, menu_selector(DialogLayer::okMenuItemCallback));
	exitMenuItem->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 50));
	exitMenuItem->setFontSize(80);
    
    CCMenuItemFont *retryMenuItem = CCMenuItemFont::create("Retry", this, menu_selector(DialogLayer::cancelMenuItemCallback));
	retryMenuItem->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
	retryMenuItem->setFontSize(54);
    
    m_pMenu = CCMenu::create(exitMenuItem, retryMenuItem, NULL);
    m_pMenu->setPosition(Point::ZERO);
    this->addChild(m_pMenu,1);

	EventListenerTouchOneByOne * listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch *, Event *)
	{
		return true;
	};
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void DialogLayer::onEnter()
{
    CCLayerColor::onEnter();

}

void DialogLayer::onExit()
{
    CCLayerColor::onExit();
    //CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
}

bool DialogLayer::onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    
    return true;
}

void DialogLayer::onTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void DialogLayer::onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void DialogLayer::onTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void DialogLayer::okMenuItemCallback(cocos2d::CCObject *pSender)
{
    // 点击确定就退出（拷贝的原有方法）
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void DialogLayer::cancelMenuItemCallback(cocos2d::CCObject *pSender)
{
	
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	//Director::getInstance()->popScene();
	auto scene = Scene::create();
	auto *layer = HelloWorld::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}
