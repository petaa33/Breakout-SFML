#pragma once
#include "entity.h"
#include "components.h"
#include <string>

class Ball : public Entity {
private:
	void bounce(sf::Vector2f normal);
public:
	Ball(const std::string& name, const sf::Vector2f& startPos, sf::Vector2f& velocity);

	void onCollision(const sf::Vector2f& normal, const Entity& collidingObj) override;
	void onCollisionPlayer(const sf::Vector2f& position);
};