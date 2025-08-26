#include "block.h"

Block::Block(sf::Vector2f position) {
	isAlive = true;
	
	health = 1;
	texture = sf::Texture("block.png");
	sprite = std::make_shared<sf::Sprite>(texture);
	sprite->setPosition(position);
}

void Block::onCollision(sf::Vector2f normal) {

}