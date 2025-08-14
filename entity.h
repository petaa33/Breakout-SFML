#pragma once
#include "SFML/Graphics.hpp"
#include "components.h"

class Entity {
public:
	std::string tag;
	sf::Texture texture;
	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<Rigidbody> body;

	virtual void onCollision() = 0;
	Entity() {};
};