#pragma once
#include "entity.h"
#include "enums.hpp"

class Paddle : public Entity {
public:
	void onCollision(const sf::Vector2f& normal, const Entity& collidingObj) override;
	void handleInput();
	Paddle() {};
	Paddle(const sf::Vector2f& startPos);
	sf::Vector2f normalXTowardPaddle(const sf::Shape& shape);
};