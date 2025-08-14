#pragma once
#include "SFML/Graphics.hpp"

class Rigidbody {
public:
	sf::Vector2f velocity = sf::Vector2f(0,0);
	float speed = 1;
	bool applyGravity = false;

	Rigidbody(float speed, float gravity) : speed(speed), applyGravity(applyGravity) {};
};
