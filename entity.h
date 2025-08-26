#pragma once
#include "SFML/Graphics.hpp"
#include "components.h"

class Entity {
public:
	bool isAlive = true;
	std::string tag;
	sf::Texture texture;
	std::shared_ptr<sf::Shape> shape;
	std::shared_ptr<Rigidbody> body;

	virtual void onCollision(sf::Vector2f normal) = 0;
	Entity() {};
};