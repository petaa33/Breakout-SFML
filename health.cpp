#pragma once
#include "health.h"

Health::Health(const int windowWidth) {
	texture = std::make_unique<sf::Texture>("health.png");

	for (int i = 0; i < 3; i++) {
		sf::Sprite heart(*texture);
		heart.setOrigin(sf::Vector2f(heart.getGlobalBounds().size.x, 0));
		heart.setPosition(sf::Vector2f(windowWidth - (i * 50) - 10, 10));

		sprites.push_back(heart);
	}
}

int Health::getValue() {
	return value;
}

void Health::update(Operation operation) {
	switch (operation) {
		case Operation::ADD: value++; break;
		case Operation::REMOVE: value--; break;
	}
}

const std::vector<sf::Sprite>& Health::getSprites() {
	return sprites;
}

void Health::add() {
	sf::Sprite heart(*texture);

	heart.setOrigin(sf::Vector2f(heart.getGlobalBounds().size.x, 0));
	heart.setPosition(sf::Vector2f((sprites.size() + 1) * 50 - 10, 10));

	sprites.push_back(heart);
}

void Health::remove() {
	sprites.pop_back();
}


