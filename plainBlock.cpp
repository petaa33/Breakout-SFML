#include "plainBlock.h"
#include "score.h"

PlainBlock::PlainBlock(const std::string& name, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color) : Block(name, sf::Texture("block.png"), size, position, color) {
	health = 1;
	points = 15;
	shape->setTexture(&texture);
}

void PlainBlock::onCollision(const sf::Vector2f& normal, const Entity& collidingObj) {
	if (collidingObj.tag == utils::EntityTag::Ball) {
		Score::getInstance().updateScore(points);
		isAlive = false;
	}
}