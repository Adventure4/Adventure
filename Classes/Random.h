#ifndef  RANDOM_H_
#define  RANDOM_H_

#include "cocos2d.h"
#include "Global.h"

USING_NS_CC;

class Random :public Layer
{
public:
	Random();
	~Random();
	static cocos2d::Scene* scene();

	CREATE_FUNC(Random);

	virtual bool init();
	void select(Ref *ref);
	void time(float dt);

protected:
	static Random* random;
	Size visibleSize;
	
};

#endif