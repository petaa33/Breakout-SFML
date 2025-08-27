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
	void onCollision(sf::Vector2f normal) override {};
	static int windowWidth;
	static int windowHeight;
};