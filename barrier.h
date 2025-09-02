#pragma once
#include "entity.h"
#include "SFML/graphics.hpp"

enum Bound {
	TOP,
	RIGHT,
	LEFT
};

class Barrier : public Entity {
public:
	Barrier() {};
	Barrier(Bound bound);
	void onCollision(const sf::Vector2f& normal, const Entity& collidingObj) override {};
	static int windowWidth;
	static int windowHeight;
};