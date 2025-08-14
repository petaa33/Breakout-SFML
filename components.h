#pragma once
#include "SFML/Graphics.hpp"

class Rigidbody {
public:
	bool isEnabled = false;
	sf::Vector2f velocity = sf::Vector2f(0,0);
	float speed = 1;
	bool applyGravity = false;

	Rigidbody(bool isEnabled, float speed, float gravity) : isEnabled(isEnabled), speed(speed), applyGravity(applyGravity) {};
};
