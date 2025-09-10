#pragma once
#include "SFML/Audio.hpp"
#include <map>
#include <vector>

enum class SoundTag {
	BlockHit1,
	BlockHit2,
	BlockHit3,
	BlockHit4,
	BlockHit5,
	PaddleHit,
	BarrierHit,
};

typedef std::map<SoundTag, sf::SoundBuffer> SoundBufferMap;
typedef std::map<SoundTag, std::unique_ptr<sf::Sound>> SoundMap;

class Audio {
	private: 
		bool initialized = false;

		SoundBufferMap soundBufferMap;
		SoundMap soundMap;
		
		Audio() {};
	public:
		static Audio& getInstance();
		void play(SoundTag tag);
};

