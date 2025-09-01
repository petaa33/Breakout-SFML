#include "score.h"
#include <iostream>

Score Score::instance;

Score::Score() : font("yoster.ttf"), text(font) {
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(10,10));
}

Score& Score::getInstance() {
	return instance;
}

void Score::updateScore(int value) {
	instance.value += value;
	instance.text.setString("Score: " + std::to_string(instance.value));
}

const sf::Text& Score::getText() const {
	return text;
}

void Score::reset() {
	instance.value = 0;
	updateScore(0);
}