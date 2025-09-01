#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class Health {
private: 
	std::unique_ptr<sf::Texture> texture;
	std::vector<sf::Sprite> sprites;

public: 
	Health() {};
	Health(const int windowWidth);

	void add();
	void add(int size, int windowWidth);
	void remove();
	const std::vector<sf::Sprite>& getSprites();
};