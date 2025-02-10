#ifndef INVIS_OBJ_H__
#define INVIS_OBJ_H__

#include "../GameObject.h"

class InvisObj : public GameObject
{
public:
	InvisObj();
	virtual ~InvisObj() override = 0;
};

#endif