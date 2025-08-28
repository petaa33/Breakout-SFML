#pragma once
#include "entity.h"
#include "enums.hpp"

class Paddle : public Entity {
public:
	void onCollision(sf::Vector2f normal) override;
	void handleInput();
	Paddle() {};
	Paddle(sf::Vector2f startPos);
};