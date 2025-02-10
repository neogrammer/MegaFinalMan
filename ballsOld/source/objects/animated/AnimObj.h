#ifndef ANIM_OBJ_H__
#define ANIM_OBJ_H__

#include "../GameObject.h"

class AnimObj : public GameObject
{
public:
	AnimObj();
	virtual ~AnimObj() override = 0;
};

#endif