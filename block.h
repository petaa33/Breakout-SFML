#pragma once
#include "entity.h"

class Block : public Entity {
private:
protected:
	int health;
public:
	virtual void onCollision() {};
	Block(sf::Vector2f position);
};
