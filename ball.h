#pragma once
#include "entity.h"
#include "components.h"

class Ball : public Entity {
private:
	void onCollision() override;
	void bounce();
public:
	Ball() {};
	Ball(sf::Vector2f startPos);
};