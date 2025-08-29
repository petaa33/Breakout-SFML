#pragma once
#include "entity.h"

class Block : public Entity {
private:
protected:
	int health;
public:
	void onCollision(sf::Vector2f normal) override;
	Block(sf::Vector2f position, std::string& name, sf::Vector2f size, sf::Color color);
};
