#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class Health {
private: 
	int value = 3;
	std::unique_ptr<sf::Texture> texture;
	std::vector<sf::Sprite> sprites;

public: 
	Health() {};
	Health(const int windowWidth);

	int getValue();
	void add();
	void remove();
	const std::vector<sf::Sprite>& getSprites();
};