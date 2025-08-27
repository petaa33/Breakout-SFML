#pragma once
#include "entity.h"
#include "block.h"
#include "barrier.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;

class EntityManager {
private:
	EntityVec entities;
	EntityVec rigidbodyEntities;
	EntityVec entitiesToBeAdded;
	EntityVec blocks;
	EntityVec bounds;

public:
	void add(const std::shared_ptr<Entity> entity);
	void removeDead();
	void update();

	void createBlocks(int windowWidth, int windowHeight);
	void createBounds(int windowWidth, int windowHeight);

	const EntityVec& getRigidbodyEntities();
	const EntityVec& getBlocks();
	const EntityVec& getBounds();

	EntityManager() {};
};