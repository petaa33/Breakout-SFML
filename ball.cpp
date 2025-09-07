#pragma once
#include "ball.h"
#include "iostream"
#include "utils.hpp"
#include <string>

Ball::Ball(const std::string& name, const sf::Vector2f& startPos, sf::Vector2f& velocity) : Entity(utils::EntityTag::Ball, name, sf::Texture("ball.png")) {
	int radius = 12;

	shape = std::make_shared<sf::CircleShape>(radius, 12);
	shape->setOrigin(sf::Vector2f(radius / 2, radius / 2));
	shape->setPosition(startPos);
	shape->setTexture(&texture);

	int speed = 450;
	body = std::make_shared<Rigidbody>(speed, velocity);
}

void Ball::bounce(sf::Vector2f normal) {
	sf::Vector2f reflected = body->velocity - 2 * (body->velocity.dot(normal)) * normal;
	body->velocity = reflected.normalized();
}

void Ball::onCollision(const sf::Vector2f& normal, const Entity& collidingObj) {
	switch (collidingObj.tag)
	{
	case utils::EntityTag::Paddle: onCollisionPlayer(collidingObj.shape->getPosition());
		break;
	default: bounce(normal);
	}
}

void Ball::onCollisionPlayer(const sf::Vector2f& position) {
	sf::Vector2f dir = shape->getPosition() - position;
	body->velocity = dir.normalized();
}

