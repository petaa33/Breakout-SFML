#pragma once
#include <random>

namespace utils {
	enum class EntityTag {
		Entity,
		Block,
		Paddle,
		Ball,
		Barrier,
		Oil,
		Shroom,
		Rigidbody
	};

	static float randomFloat(float min, float max) {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dist(min, max);
		return dist(gen);
	}
}
