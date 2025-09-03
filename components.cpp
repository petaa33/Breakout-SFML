#pragma once
#include "components.h"
#include "game.h"
#include "iostream"

SpeedDebuff::SpeedDebuff(Entity* entity, float duration, const sf::Color& color) : Modifier(entity, duration) {
	this->entity->body->speed -= 150;
	this->entity->shape->setFillColor(color);
}

SpeedDebuff::~SpeedDebuff() {
	std::cout << "Debuff modifier deleted" << "\n";
}

void SpeedDebuff::update() {
	timePassed += Game::deltaTime;

	if (timePassed > duration) {
		entity->body->speed += 150;
		entity->shape->setFillColor(sf::Color::White);
		isActive = false;
	}
}