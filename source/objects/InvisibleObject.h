#ifndef INVISIBLE_OBJECT_H__
#define INVISIBLE_OBJECT_H__
#include "GameObject.h"
class InvisibleObject : public GameObject
{
public:
	InvisibleObject();
	virtual ~InvisibleObject() override;
};
#endif