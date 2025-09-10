#include "oilBlock.h"
#include "score.h"

OilBlock::OilBlock(const std::string& name, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, SoundTag soundTag) : Block(name, sf::Texture("oil_block.png"), size, position, color, soundTag) {
	health = 1;
	points = 25;
	shape->setTexture(&texture);

	sf::Vector2f blockOrigin(shape->getGlobalBounds().size.x / 2, shape->getGlobalBounds().size.y);
	sf::Vector2f oilPosition = shape->getPosition() + blockOrigin;
	std::string oilName = name + "_child";
	sf::Vector2f oilSize(32, 32);

	child = std::make_shared<Oil>(oilName, oilSize, oilPosition, color);
}

void OilBlock::onCollision(const sf::Vector2f& normal, const Entity& collidingObj) {
	Audio::getInstance().play(soundTag);
	Score::getInstance().updateScore(points);
	isAlive = false;
}

Oil::Oil(const std::string& name, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color) : Entity(utils::EntityTag::Oil, name, sf::Texture("oil.png")) {
	shape = std::make_shared<sf::RectangleShape>(size);
	shape->setTexture(&texture);
	shape->setPosition(position);
	shape->setFillColor(color);

	float speed = 250;
	sf::Vector2f velocity(0, 1);

	body = std::make_shared<Rigidbody>(speed, velocity);
}

void Oil::onCollision(const sf::Vector2f& normal, const Entity& collidingObj) {
	switch (collidingObj.tag)
	{
	case utils::EntityTag::Paddle: isAlive = false;
		break;
	default:
		break;
	}
}