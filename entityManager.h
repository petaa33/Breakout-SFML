#pragma once
#include "entity.h"
#include "block.h"
#include "barrier.h"
#include "map"
#include "utils.hpp"
#include <string>
#include "components.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;

struct RandomBlock {
	int index = 0;
	BlockTag tag;
};

class EntityManager {
private:
	EntityVec entitiesToBeAdded;
	std::map<utils::EntityTag, EntityVec> entitiesMap;

public:
	void add(const std::shared_ptr<Entity>& entity);
	void removeDead();
	void update();

	void createBlocks(int windowWidth, int windowHeight);
	void createBounds(int windowWidth, int windowHeight);
	void createBlockChildren();

	const EntityVec& getEntities(utils::EntityTag tag);
	EntityManager() {};
};