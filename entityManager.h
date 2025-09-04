#pragma once
#include "entity.h"
#include "block.h"
#include "barrier.h"
#include "map"
#include "enums.hpp"
#include <string>
#include "components.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;

struct RandomBlock {
	int index = 0;
	BlockTag tag;
};

class EntityManager {
private:
	EntityVec entities;
	EntityVec rigidbodyEntities;
	EntityVec entitiesToBeAdded;
	EntityVec bounds;
	EntityVec blocks;

public:
	void add(const std::shared_ptr<Entity>& entity);
	void removeDead();
	void removeEntity(const std::shared_ptr<Rigidbody> body, std::string& name);
	void update();

	void createBlocks(int windowWidth, int windowHeight);
	void createBounds(int windowWidth, int windowHeight);
	void createBlockChildren();

	const EntityVec& getRigidbodyEntities();
	const EntityVec& getBlocks();
	const EntityVec& getBounds();
	const EntityVec& getEntities();

	EntityManager() {};
};