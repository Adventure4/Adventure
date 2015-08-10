#include "cocos2d.h"

USING_NS_CC;

class aboutmenu :public Layer
{
public:
	static Scene* creatScene();
	static aboutmenu* create(PhysicsWorld* world);

	bool init(PhysicsWorld* world);

	void Exit(Ref *ref);
	void backToMenu(float f);

private:
	aboutmenu();
	~aboutmenu();

	Sprite* bgsprite;
	PhysicsWorld* m_world;
};