#pragma once
#include "block.h"

class ShroomBlock : public Block {
public:
	void onCollision(const sf::Vector2f& normal, const Entity& collidingObj) override;
	ShroomBlock(const std::string& name, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color);
};

class Shroom : public Entity {
public:
	void onCollision(const sf::Vector2f& normal, const Entity& collidingObj) override;
	Shroom(const std::string& name, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color);
};

