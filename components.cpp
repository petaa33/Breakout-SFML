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

IncreaseSize::IncreaseSize(Entity* entity, float duration) : 
	Modifier(entity, duration), 
	paddle(std::static_pointer_cast<sf::RectangleShape>(entity->shape)),
	startSize(paddle.lock()->getSize()),
	colorNotifyDelay(duration - 1) {};

void IncreaseSize::update() {
	timePassed += Game::deltaTime;

	float t = timePassed / duration;
	
	if (t <= 1) {
		float x = startSize.x + (targetSize - startSize.x) * t;
		paddle.lock()->setSize(sf::Vector2f(x, startSize.y));
	}

	if (timePassed >= colorNotifyDelay) {
		flashColor();
	}

	if (timePassed > duration) {
		entity->shape->setFillColor(sf::Color::White);
		paddle.lock()->setSize(startSize);
		isActive = false;
	}
}

void IncreaseSize::flashColor() {
	colorTimePassed += Game::deltaTime;

	if (colorTimePassed >= colorDuration) {
		sf::Color color = entity->shape->getFillColor() == main ? secondary : main;
		entity->shape->setFillColor(color);
		colorTimePassed = 0;
	}
}

IncreaseSize::~IncreaseSize() {
	std::cout << "IncreaseSize modifier destoryed" << "\n";
}