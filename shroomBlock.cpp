#include "shroomBlock.h"

ShroomBlock::ShroomBlock(const std::string& name, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color) : 
	Block(name, sf::Texture("shroom_block.png"), size, position, color) {

	shape->setTexture(&texture);

	sf::Vector2f blockOrigin(shape->getGlobalBounds().size.x / 2, shape->getGlobalBounds().size.y);
	sf::Vector2f shroomPosition = shape->getPosition() + blockOrigin;
	std::string shroomName = name + "_child";
	sf::Vector2f shroomSize(32, 32);

	child = std::make_shared<Shroom>(shroomName, shroomSize, shroomPosition, color);
}

void ShroomBlock::onCollision(const sf::Vector2f& normal, const Entity& collidingObj) {
	isAlive = false;
};

Shroom::Shroom(const std::string& name, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color) : Entity(utils::EntityTag::Shroom, name, sf::Texture("shroom.png")) {
	shape = std::make_shared<sf::RectangleShape>(size);
	shape->setTexture(&texture);
	shape->setPosition(position);
	shape->setFillColor(color);

	float speed = 250;
	sf::Vector2f velocity(0, 1);

	body = std::make_shared<Rigidbody>(speed, velocity);
}

void Shroom::onCollision(const sf::Vector2f& normal, const Entity& collidingObj) {
	if (collidingObj.tag == utils::EntityTag::Paddle) {
		isAlive = false;
	}
}