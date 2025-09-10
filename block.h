#pragma once
#include "entity.h"
#include "audio.h"

enum class BlockTag {
	HARD,
	OIL,
	SHROOM,
	BLOCK_TAG_MAX
};

BlockTag getRandomBlockTag();

class Block : public Entity {
private:
protected:
	int health = 0;
	int points = 50;
	SoundTag soundTag;

public:
	std::shared_ptr<Entity> child = nullptr;
	static sf::Color getBlockColor(int index);

	Block(const std::string& name, const sf::Texture& texture, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, SoundTag soundTag);
	Block() {};
	~Block() {};
};
