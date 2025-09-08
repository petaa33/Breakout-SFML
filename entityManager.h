#pragma once
#include "entity.h"
#include "block.h"
#include "barrier.h"
#include "map"
#include "utils.hpp"
#include <string>
#include "components.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::vector<std::weak_ptr<Entity>> EntityVecWeak;

struct RandomBlock {
	int index = 0;
	BlockTag tag;
};

class EntityManager {
private:
	EntityVec entities;
	EntityVec entitiesToBeAdded;

	std::map<utils::EntityTag, EntityVecWeak> entitiesMap;
public:
	void add(const std::shared_ptr<Entity>& entity);
	void removeDead();
	void update();
	void reset();

	void createBlocks(int windowWidth, int windowHeight);
	void createBounds(int windowWidth, int windowHeight);
	void createBlockChildren();

	const EntityVec& getEntities();
	const EntityVecWeak& getEntities(utils::EntityTag tag);
	EntityManager() {};
};