#pragma once
#include "paddle.h"
#include "components.h"

Paddle::Paddle(sf::Vector2f startPos) {
	isAlive = true;
	int width = 128;
	int height = 32;

	texture = sf::Texture("paddle.png");
	sprite = std::make_shared<sf::Sprite>(texture);
	sprite->setOrigin(sf::Vector2f(width / 2, height / 2));
	sprite->setPosition(startPos);

	bool isEnabled = true;
	int speed = 25;
	bool hasGravity = false;

	body = std::make_shared<Rigidbody>(isEnabled, speed, hasGravity);
}

void Paddle::onCollision() {

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

