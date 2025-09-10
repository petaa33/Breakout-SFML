#include "hardBlock.h"
#include "score.h"

HardBlock::HardBlock(const std::string& name, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, SoundTag soundTag) : Block(name, sf::Texture("hard_block.png"), size, position, color, soundTag) {
	health = 2;
	points = 50;
	shape->setTexture(&texture);
}

void HardBlock::onCollision(const sf::Vector2f& normal, const Entity& collidingObj) {
	if (collidingObj.tag == utils::EntityTag::Ball) {
		Audio::getInstance().play(soundTag);

		health--;

		if (health <= 0) {
			isAlive = false;
			Score::getInstance().updateScore(points);
			return;
		}

		texture.loadFromFile("broken_block.png");
	}
}