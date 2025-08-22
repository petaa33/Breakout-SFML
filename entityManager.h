#pragma once
#include "entity.h"
#include "block.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;

class EntityManager {
private:
	EntityVec entities;
	// Entites that can move
	EntityVec rigidbodyEntities;
	EntityVec entitiesToBeAdded;
	EntityVec blocks;

public:
	void add(const std::shared_ptr<Entity> entity);
	void removeDead();
	void update();
	void createBlocks(int windowWidth, int windowHeight);

	const EntityVec& getRigidbodyEntities();
	const EntityVec& getBlocks();
	EntityManager() {};
};