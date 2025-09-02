#pragma once
#include "entity.h"
#include "components.h"
#include <string>

class Ball : public Entity {
private:
	void bounce();
public:
	Ball() {};
	Ball(const sf::Vector2f& startPos);
	void onCollision(const sf::Vector2f& normal, const Entity& collidingObj) override;
	void onCollisionPlayer(const sf::Vector2f& position);
};