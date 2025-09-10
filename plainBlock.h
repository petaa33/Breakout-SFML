#pragma once
#include "block.h"

class PlainBlock : public Block {
public:
	void onCollision(const sf::Vector2f& normal, const Entity& collidingObj) override;
	PlainBlock(const std::string& name, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, SoundTag soundTag);
};