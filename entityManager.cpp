#include "entityManager.h"
#include <algorithm>

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
	entities.erase(std::remove_if(
		entities.begin(),
		entities.end(), 
		[&](std::shared_ptr<Entity>& entity) {
			if (!entity->isAlive) {
				removeEntity(entity->tag, entity->name);
				return true;
			}
			return false;
		}),
		entities.end());
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

const EntityVec& EntityManager::getEntities() {
	return entities;
}

void EntityManager::createBlocks(int windowWidth, int windowHeight) {
	int blockWidth = 160;
	int blockHeight = 50;
	int numOfBlocksX = windowWidth / blockWidth;
	int numOfBlocksY = 5;
	int verticalGap = 75;

	int min = 0;
	int max = numOfBlocksX * numOfBlocksY;

	std::array<int, 8> hardblockIndexes;

	for (int i = 0; i < hardblockIndexes.size(); i++) {
		hardblockIndexes[i] = rand() % (max - min + 1) + min;
	}

	for (int i = 0; i < numOfBlocksX; i++) {
		for (int j = 0; j < numOfBlocksY; j++) {
			int index = i + j * numOfBlocksX;

			std::string name = "Block-" + std::to_string(i) + std::to_string(j);
			sf::Vector2f size(blockWidth, blockHeight);
			sf::Color color = Block::getBlockColor(j);
			sf::Vector2f position(i * blockWidth, j * blockHeight + verticalGap);
			std::shared_ptr<Block> block;

			if (std::find(hardblockIndexes.begin(), hardblockIndexes.end(), index) != hardblockIndexes.end()) {
				block = std::make_shared<HardBlock>(position, name, size, color);
			}
			else {
				block = std::make_shared<PlainBlock>(position, name, size, color);
			}

			blocks.push_back(block);
			add(block);
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

void EntityManager::removeEntity(utils::EntityTag tag, std::string& name) {
	EntityVec* entities = nullptr;

	switch (tag)
	{
	case utils::Block:
		entities = &blocks;
		break;
	case utils::Paddle:
		break;
	case utils::Ball:
		entities = &rigidbodyEntities;
		break;
	case utils::Barrier:
		break;
	default:
		break;
	}

	auto it = std::find_if(entities->begin(), entities->end(), [&](std::shared_ptr<Entity>& entity) { return entity->name == name; });
	if (it != entities->end()) {
		entities->erase(it);
	}
}

