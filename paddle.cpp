#pragma once
#include "paddle.h"
#include "components.h"

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

