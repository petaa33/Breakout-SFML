#include "block.h"
#include <iostream>

Block::Block(sf::Vector2f position, std::string& name, sf::Vector2f size, sf::Color color) {
	tag = utils::EntityTag::Block;
	this->name = name;
	isAlive = true;
	
	health = 1;
	texture = sf::Texture("block.png");
	shape = std::make_shared<sf::RectangleShape>(size);
	shape->setPosition(position);
	shape->setFillColor(color);
	shape->setTexture(&texture);

	body = std::make_shared<Rigidbody>(false, 0, 0);
}

void Block::onCollision(sf::Vector2f normal) {
	health--;

	if (health <= 0) {
		isAlive = false;
	}
}