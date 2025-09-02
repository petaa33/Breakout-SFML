#pragma once
#include "SFML/Graphics.hpp"

class Rigidbody {
public:
	float speed = 1;
	sf::Vector2f velocity = sf::Vector2f(0,0);

	Rigidbody(float speed, sf::Vector2f& velocity) : speed(speed), velocity(velocity) {};
};
