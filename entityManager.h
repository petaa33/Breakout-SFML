#pragma once
#include "entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;

class EntityManager {
private:
	EntityVec entities;
	// Entites that can move
	EntityVec rigidbodyEntities;
	EntityVec entitiesToBeAdded;

public:
	void add(const std::shared_ptr<Entity> entity);
	void removeDead();
	void update();
	const EntityVec& getRigidbodyEntities();
	EntityManager() {};
};