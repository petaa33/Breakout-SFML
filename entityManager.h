#pragma once
#include "entity.h"
#include "block.h"
#include "barrier.h"
#include "map"
#include "enums.hpp"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;

class EntityManager {
private:
	EntityVec entities;
	EntityVec rigidbodyEntities;
	EntityVec entitiesToBeAdded;
	EntityVec bounds;
	EntityVec blocks;

public:
	void add(const std::shared_ptr<Entity> entity);
	void removeDead();
	void removeEntity(utils::EntityTag tag, std::string& name);
	void update();

	void createBlocks(int windowWidth, int windowHeight);
	void createBounds(int windowWidth, int windowHeight);

	const EntityVec& getRigidbodyEntities();
	const EntityVec& getBlocks();
	const EntityVec& getBounds();
	const EntityVec& getEntities();

	EntityManager() {};
};