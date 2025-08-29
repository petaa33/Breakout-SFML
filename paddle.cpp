#pragma once
#include "paddle.h"
#include "components.h"

Paddle::Paddle(sf::Vector2f startPos) {
	tag = utils::EntityTag::Paddle;
	isAlive = true;
	int width = 128;
	int height = 32;

	texture = sf::Texture("paddle.png");
	shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
	shape->setOrigin(sf::Vector2f(width / 2, height / 2));
	shape->setPosition(startPos);
	shape->setTexture(&texture);

	bool isEnabled = true;
	int speed = 450;
	bool hasGravity = false;

	body = std::make_shared<Rigidbody>(isEnabled, speed, hasGravity);
}

void Paddle::onCollision(sf::Vector2f normal) {

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

