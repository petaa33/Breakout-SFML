#include "block.h"

Block::Block(sf::Vector2f position) {
	isAlive = true;
	
	health = 1;
	texture = sf::Texture("block.png");
	shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(128,32));
	shape->setPosition(position);
}

void Block::onCollision(sf::Vector2f normal) {

}