#include "block.h"
#include "score.h"
#include <iostream>

BlockTag getRandomBlockTag() {
	int max = static_cast<int>(BlockTag::BLOCK_TAG_MAX) - 1;
	int min = 0;

	return static_cast<BlockTag>(rand() % (max - min + 1) + min);
}
sf::Color Block::getBlockColor(int index) {
	switch (index)
	{
	case 0: return sf::Color::Blue;
	case 1: return sf::Color::Red;
	case 2: return sf::Color::Yellow;
	case 3: return sf::Color::Green;
	case 4: return sf::Color::Magenta;
	default:
		return sf::Color::White;
	}
}

Block::Block(const std::string& name, const sf::Texture& texture, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color) : Entity(utils::EntityTag::Block, name, texture) {
	shape = std::make_shared<sf::RectangleShape>(size);
	shape->setPosition(position);
	shape->setFillColor(color);
}


