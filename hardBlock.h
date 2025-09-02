#pragma once
#include "block.h"

class HardBlock : public Block {
public:
	void onCollision(const sf::Vector2f& normal, const Entity& collidingObj) override;
	HardBlock(const std::string& name, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color);
};

