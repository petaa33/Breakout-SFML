#include "entityManager.h"
#include "plainBlock.h"
#include "hardBlock.h"
#include "oilBlock.h"
#include "shroomBlock.h"
#include <algorithm>
#include <random>
#include <iostream>

void EntityManager::add(const std::shared_ptr<Entity>& entity) {
	entitiesToBeAdded.push_back(entity);
}

void EntityManager::update() {
	createBlockChildren();
	removeDead();

	for (std::shared_ptr<Entity> e : entitiesToBeAdded) {
		if (e->body) {
			entitiesMap[utils::EntityTag::Rigidbody].push_back(e);
		}

		entitiesMap[e->tag].push_back(e);
		entitiesMap[utils::EntityTag::Entity].push_back(e);
	}

	entitiesToBeAdded.clear();
}

void EntityManager::removeDead() {
	for (auto& [key, entityVec] : entitiesMap) {
		entitiesMap[key].erase(std::remove_if(
			entityVec.begin(),
			entityVec.end(),
			[&](std::shared_ptr<Entity>& entity) {
				return !entity->isAlive;
			}),
			entityVec.end());
	}
}

const EntityVec& EntityManager::getEntities(utils::EntityTag tag) {
	return entitiesMap[tag];
}

void EntityManager::createBlocks(int windowWidth, int windowHeight) {
	int blockWidth = 160;
	int blockHeight = 50;
	int numOfBlocksX = windowWidth / blockWidth;
	int numOfBlocksY = 5;
	int verticalGap = 75;

	int min = 0;
	int max = numOfBlocksX * numOfBlocksY;

	std::vector<int> pool;
	pool.reserve(max);

	for (int i = 0; i < max; i++) {
		pool.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(pool.begin(), pool.end(), g);

	std::array<RandomBlock, 10> uniqueBlocks;
	
	for (int i = 0; i < uniqueBlocks.size(); i++) {
		std::cout << pool[i] << "\n";
		uniqueBlocks[i].index = pool[i];
		uniqueBlocks[i].tag = getRandomBlockTag();
	}

	for (int i = 0; i < numOfBlocksX; i++) {
		for (int j = 0; j < numOfBlocksY; j++) {
			int index = i + j * numOfBlocksX;

			std::string name = "Block-" + std::to_string(i) + std::to_string(j);
			sf::Vector2f size(blockWidth, blockHeight);
			sf::Color color = Block::getBlockColor(j);
			sf::Vector2f position(i * blockWidth, j * blockHeight + verticalGap);
			std::shared_ptr<Block> block;

			auto it = std::find_if(uniqueBlocks.begin(), uniqueBlocks.end(), [index](RandomBlock block) {return block.index == index; });

			switch (it->tag)
			{
			case BlockTag::HARD: block = std::make_shared<HardBlock>(name, size, position, color);
				break;
			case BlockTag::OIL: block = std::make_shared<OilBlock>(name, size, position, color);
				break;
			case BlockTag::SHROOM: block = std::make_shared<ShroomBlock>(name, size, position, color);
				break;
			default:
				block = std::make_shared<PlainBlock>(name, size, position, color);
				break;
			}

			entitiesMap[utils::EntityTag::Block].push_back(block);
			add(block);
		}
	}
}

void EntityManager::createBounds(int windowWidth, int windowHeight) {
	Barrier::windowWidth = windowWidth;
	Barrier::windowHeight = windowHeight;

	entitiesMap[utils::EntityTag::Barrier].push_back(std::make_shared<Barrier>(Bound::TOP));
	entitiesMap[utils::EntityTag::Barrier].push_back(std::make_shared<Barrier>(Bound::LEFT));
	entitiesMap[utils::EntityTag::Barrier].push_back(std::make_shared<Barrier>(Bound::RIGHT));
}

void EntityManager::createBlockChildren() {
	for (auto& entity : entitiesMap[utils::EntityTag::Block]) {
		auto block = std::static_pointer_cast<Block>(entity);
		if (!block->isAlive && block->child) {
			add(block->child);
		}
	}
}

