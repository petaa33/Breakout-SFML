#pragma once
#include "barrier.h"
#include "SFML/Graphics.hpp"

int Barrier::windowWidth = 0;
int Barrier::windowHeight = 0;

Barrier::Barrier(Bound bound) {
	tag = "Barrier";
	
	float width = 0;
	float height = 0;
	sf::Vector2f origin;
	sf::Vector2f position;
	
	switch (bound)
	{
		case TOP:
			width = Barrier::windowWidth;
			height = 1;
			position = sf::Vector2f(width/2, 0);
			break;
		case RIGHT:
			width = 1;
			height = Barrier::windowHeight;
			position = sf::Vector2f(Barrier::windowWidth, height/2);
			break;
		case LEFT:
			width = 1;
			height = Barrier::windowHeight;
			position = sf::Vector2f(1, height / 2);
			break;
		default:
			break;
	}

	origin = sf::Vector2f(width / 2, height / 2);

	shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
	shape->setOrigin(origin);
	shape->setPosition(position);
	shape->setFillColor(sf::Color::Green);
}
