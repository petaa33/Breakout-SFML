#pragma once
#include "entity.h"

enum class BlockTag {
	PLAIN,
	HARD,
	OIL,
	BLOCK_TAG_MAX
};

BlockTag getRandomBlockTag();

class Block : public Entity {
private:
protected:
	int health = 0;
public:
	static sf::Color getBlockColor(int index);
	Block(sf::Vector2f position, std::string& name, sf::Vector2f size, sf::Color color);
	Block() {};
	~Block();
};

class PlainBlock : public Block {
public: 
	void onCollision(sf::Vector2f normal) override;
	PlainBlock(sf::Vector2f position, std::string& name, sf::Vector2f size, sf::Color color);
};

class HardBlock : public Block {
public:
	void onCollision(sf::Vector2f normal) override;
	HardBlock(sf::Vector2f position, std::string& name, sf::Vector2f size, sf::Color color);
};

class OilBlock : public Block {
private:

public:
	void onCollision(sf::Vector2f normal) override;
	OilBlock(sf::Vector2f position, std::string& name, sf::Vector2f size, sf::Color color);
};
