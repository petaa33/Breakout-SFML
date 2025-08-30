#include "block.h"
#include "score.h"
#include <iostream>

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

Block::Block(sf::Vector2f position, std::string& name, sf::Vector2f size, sf::Color color) {
	tag = utils::EntityTag::Block;
	this->name = name;
	isAlive = true;
	
	shape = std::make_shared<sf::RectangleShape>(size);
	shape->setPosition(position);
	shape->setFillColor(color);

	body = std::make_shared<Rigidbody>(false, 0, 0);
}

Block::~Block() {
	Score::getInstance().updateScore(50);
}

PlainBlock::PlainBlock(sf::Vector2f position, std::string& name, sf::Vector2f size, sf::Color color) : Block(position, name, size, color) {
	health = 1;
	texture = sf::Texture("block.png");
	shape->setTexture(&texture);
}

void PlainBlock::onCollision(sf::Vector2f normal) {
	isAlive = false;
}

HardBlock::HardBlock(sf::Vector2f position, std::string& name, sf::Vector2f size, sf::Color color) : Block(position, name, size, color) {
	health = 2;
	texture = sf::Texture("hard_block.png");
	shape->setTexture(&texture);
}

void HardBlock::onCollision(sf::Vector2f normal) {
	health--;
	
	if (health <= 0) {
		isAlive = false;
	}

	texture.loadFromFile("broken_block.png");
}