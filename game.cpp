#include "game.h"

Game::Game() {
	windowWidth = 1200;
	windowHeight = 720;
	window = sf::RenderWindow(sf::VideoMode({ windowWidth, windowHeight }), "Breakout game");

	sf::Vector2f playerStartPos(windowWidth/2, windowHeight - 100);
	sf::Vector2f ballStartPos(windowWidth/2, windowHeight/2);

	paddle = std::make_shared<Paddle>(playerStartPos);
	ball = std::make_shared<Ball>(ballStartPos);
}

void Game::run() {
	systemRender();
}

void Game::systemRender() {
	window.clear(sf::Color::Black);
	window.draw(*paddle->sprite);
	window.draw(*ball->sprite);
	window.display();
}

void Game::sytemCollison() {

}

void Game::systemMovement() {

}

void Game::systemInput() {

}

void Game::handleDeltaTime() {

}

std::shared_ptr<Paddle> createPaddle() {

}