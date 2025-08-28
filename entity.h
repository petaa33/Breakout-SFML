#pragma once
#include "SFML/Graphics.hpp"
#include "components.h"
#include "enums.hpp"

class Entity {
public:
	bool isAlive = true;
	utils::EntityTag tag;
	std::string name = "Entity";
	sf::Texture texture;
	std::shared_ptr<sf::Shape> shape;
	std::shared_ptr<Rigidbody> body;

	virtual void onCollision(sf::Vector2f normal) = 0;
	Entity() {};
};