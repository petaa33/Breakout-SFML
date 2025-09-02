#pragma once
#include "block.h"

class OilBlock : public Block {
private:
public:
	void onCollision(const sf::Vector2f& normal, const Entity& collidingObj) override;
	OilBlock(const std::string& name, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color);
};

class Oil : public Entity {
public:
	void onCollision(const sf::Vector2f& normal, const Entity& collidingObj) override;
	Oil() {};
	Oil(const std::string& name, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color);
};