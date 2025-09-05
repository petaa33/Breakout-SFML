#pragma once
#include "SFML/Graphics.hpp"

class Entity;

class Rigidbody {
public:
	float speed = 1;
	sf::Vector2f velocity = sf::Vector2f(0,0);

	Rigidbody(float speed, sf::Vector2f& velocity) : speed(speed), velocity(velocity) {};
};

class Modifier {
protected:
	float duration = 0;
	float timePassed = 0;
	bool effectApplied = false;
	sf::Clock clock;
	Entity* entity = nullptr;

public:
	bool isActive = true;
	virtual void update() = 0;
	Modifier() {};
	Modifier(Entity* entity, float duration) : entity(entity), duration(duration) {};
	virtual ~Modifier() {};
};

class SpeedDebuff : public Modifier {
private:
	float debuf = 100;

public:
	SpeedDebuff() {};
	SpeedDebuff(Entity* entity, float duration, const sf::Color& color);
	~SpeedDebuff();
	void update() override;
};

class IncreaseSize : public Modifier {
private:
	sf::Color main = sf::Color::White;
	sf::Color secondary = sf::Color(100, 100, 100, 255);

	std::weak_ptr<sf::RectangleShape> paddle;
	
	float targetSize = 250;
	sf::Vector2f startSize;
	float increasedBy = 0;

	float colorNotifyDelay = duration - 1;
	float colorDuration = 0.1f;
	float colorTimePassed = 0;

	void flashColor();
public:
	IncreaseSize(Entity* entity, float duration);
	~IncreaseSize();
	void update() override;
};