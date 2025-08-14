#pragma once
#include "entity.h"

class Paddle : public Entity {
public:
	void onCollision() override;
	void handleInput();
	Paddle() {};
	Paddle(sf::Vector2f startPos);
};