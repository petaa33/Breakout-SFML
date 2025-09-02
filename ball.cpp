#pragma once
#include "ball.h"
#include "iostream"
#include "enums.hpp"
#include <string>

Ball::Ball(const sf::Vector2f& startPos) : Entity(utils::EntityTag::Ball, "Ball", sf::Texture("ball.png")) {
	int radius = 12;

	shape = std::make_shared<sf::CircleShape>(radius, 12);
	shape->setOrigin(sf::Vector2f(radius / 2, radius / 2));
	shape->setPosition(startPos);
	shape->setTexture(&texture);

	int speed = 450;
	sf::Vector2f velocity(0, -1);

	body = std::make_shared<Rigidbody>(speed, velocity);
}

void Ball::bounce() {
}

void Ball::onCollision(const sf::Vector2f& normal, const Entity& collidingObj) {
	if(collidingObj.tag == utils::EntityTag::Paddle) {
		onCollisionPlayer(collidingObj.shape->getPosition());
		return;
	}
	sf::Vector2f reflected = body->velocity - 2 * (body->velocity.dot(normal)) * normal;
	body->velocity = reflected.normalized();
}

void Ball::onCollisionPlayer(const sf::Vector2f& position) {
	sf::Vector2f dir = shape->getPosition() - position;
	body->velocity = dir.normalized();
}

