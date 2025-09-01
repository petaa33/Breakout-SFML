#pragma once
#include "SFML/Graphics.hpp"

class Score {
private:
	sf::Font font;
	sf::Text text;

	int value = 0;

	Score();
	Score(Score const&) = delete;
	void operator=(Score const&) = delete;

	static Score instance;

public:
	static Score& getInstance();
	void updateScore(int value);
	const sf::Text& getText() const;
	void reset();
};