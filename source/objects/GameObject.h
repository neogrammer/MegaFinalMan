#ifndef GAME_OBJECT_H__
#define GAME_OBJECT_H__

class GameObject
{

public:
	GameObject();
	virtual ~GameObject();

	virtual void update(float gameTime);
};
#endif