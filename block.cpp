#include "block.h"
#include <iostream>

Block::Block(sf::Vector2f position, std::string& name) {
	tag = utils::EntityTag::Block;
	this->name = name;
	isAlive = true;
	
	health = 1;
	texture = sf::Texture("block.png");
	shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(128,32));
	shape->setPosition(position);
	shape->setTexture(&texture);

	body = std::make_shared<Rigidbody>(false, 0, 0);
}

void Block::onCollision(sf::Vector2f normal) {
	std::cout << "HIT";
	health--;

	if (health <= 0) {
		isAlive = false;
	}
}