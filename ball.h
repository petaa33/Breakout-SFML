#pragma once
#include "entity.h"
#include "components.h"

class Ball : public Entity {
private:
	void bounce();
public:
	Ball() {};
	Ball(sf::Vector2f startPos);
	void onCollision(sf::Vector2f normal) override;
	void onCollisionPlayer(const sf::Vector2f& position);
};