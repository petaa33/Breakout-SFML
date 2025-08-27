#include "entityManager.h"

void EntityManager::add(const std::shared_ptr<Entity> entity) {
	entitiesToBeAdded.push_back(entity);
}

void EntityManager::update() {
	removeDead();

	for (std::shared_ptr<Entity> e : entitiesToBeAdded) {
		if (e->body->isEnabled) {
			rigidbodyEntities.push_back(e);
		}
		entities.push_back(e);
	}

	entitiesToBeAdded.clear();
}

void EntityManager::removeDead() {
	
}

const EntityVec& EntityManager::getRigidbodyEntities() {
	return rigidbodyEntities;
}

const EntityVec& EntityManager::getBlocks() {
	return blocks;
}

const EntityVec& EntityManager::getBounds() {
	return bounds;
}

void EntityManager::createBlocks(int windowWidth, int windowHeight) {
	int blockWidth = 128;
	int blockHeight = 32;
	int numOfBlocksX = windowWidth / blockWidth;
	int numOfBlocksY = 5;

	for (int i = 0; i < numOfBlocksX; i++) {
		for (int j = 0; j < numOfBlocksY; j++) {
			std::shared_ptr<Block> block = std::make_shared<Block>(sf::Vector2f(i * blockWidth, j * blockHeight));
			blocks.push_back(block);
		}
	}
}

void EntityManager::createBounds(int windowWidth, int windowHeight) {
	Barrier::windowWidth = windowWidth;
	Barrier::windowHeight = windowHeight;

	bounds.push_back(std::make_shared<Barrier>(Bound::TOP));
	bounds.push_back(std::make_shared<Barrier>(Bound::LEFT));
	bounds.push_back(std::make_shared<Barrier>(Bound::RIGHT));
}

