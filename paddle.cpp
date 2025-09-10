#pragma once
#include "paddle.h"
#include "components.h"
#include <iostream>
#include "audio.h"

Paddle::Paddle(const sf::Vector2f& startPos) : Entity(utils::EntityTag::Paddle, "Paddle", sf::Texture("paddle.png")) {
	int width = 128;
	int height = 32;

	shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
	shape->setOrigin(sf::Vector2f(width / 2, height / 2));
	shape->setPosition(startPos);
	shape->setTexture(&texture);

	int speed = 450;
	sf::Vector2f velocity(0,0);

	body = std::make_shared<Rigidbody>(speed, velocity);
}

void Paddle::onCollision(const sf::Vector2f& normal, const Entity& collidingObj) {
	Audio::getInstance().play(SoundTag::PaddleHit);

	switch (collidingObj.tag)
	{
	case utils::EntityTag::Oil: modifiers.push_back(std::make_unique<SpeedDebuff>(this, 2.5f, collidingObj.shape->getFillColor()));
		break;
	case utils::EntityTag::Shroom: modifiers.push_back(std::make_unique<IncreaseSize>(this, 5));
		break;
	default:
		break;
	}
}

void Paddle::handleInput() {
	body->velocity.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		body->velocity.x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		body->velocity.x = 1;
	}
}

sf::Vector2f Paddle::normalXTowardPaddle(const sf::Shape& shape) {
	sf::Vector2f dir = this->shape->getPosition() - shape.getPosition();
	return dir.dot(sf::Vector2f(1, 0)) > 0 ? sf::Vector2f(1, 0) : sf::Vector2f(-1, 0);
}

