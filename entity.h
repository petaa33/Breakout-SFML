#pragma once
#include "SFML/Graphics.hpp"
#include "components.h"
#include "enums.hpp"

class Entity {
public:
	bool isAlive = true;
	utils::EntityTag tag = utils::EntityTag::Block;
	std::string name = "Entity";
	sf::Texture texture;

	std::shared_ptr<sf::Shape> shape = nullptr;
	std::shared_ptr<Rigidbody> body = nullptr;
	std::vector<std::unique_ptr<Modifier>> modifiers;

	virtual void onCollision(const sf::Vector2f& normal, const Entity& collidingObj) = 0;

	Entity() {};
	Entity(utils::EntityTag tag, const std::string& name, const sf::Texture& texture) : tag(tag), name(name), texture(texture) {};
};