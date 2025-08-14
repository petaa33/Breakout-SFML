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

