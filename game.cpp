#include "game.h"

Game::Game() {
	windowWidth = 1200;
	windowHeight = 720;
	window = sf::RenderWindow(sf::VideoMode({ windowWidth, windowHeight }), "Breakout game");

	sf::Vector2f playerStartPos(windowWidth/2, windowHeight - 100);
	sf::Vector2f ballStartPos(windowWidth/2, windowHeight/2);

	paddle = std::make_shared<Paddle>(playerStartPos);
	ball = std::make_shared<Ball>(ballStartPos);

	entityManager.add(paddle);
	entityManager.add(ball);

	clock = sf::Clock();
}

void Game::run() {
	handleDeltaTime();
	systemInput();
	systemMovement();
	systemRender();
	entityManager.update();
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
	for (auto& entity : entityManager.getRigidbodyEntities()) {
		entity->sprite->move(entity->body->velocity * entity->body->speed * deltaTime);
	}
}

void Game::systemInput() {
	paddle->handleInput();
}

void Game::handleDeltaTime() {
	deltaTime = clock.restart().asSeconds();
}

std::shared_ptr<Paddle> createPaddle() {

}