#include "audio.h"
#include "SFML/Audio.hpp"
#include <iostream>
#include <map>
#include <string>

void Audio::play(SoundTag soundTag) {
	Audio::getInstance().soundMap[soundTag]->play();
}

Audio& Audio::getInstance() {
	static Audio instance;

	if (!instance.initialized) {
		instance.soundBufferMap[SoundTag::BlockHit1] = sf::SoundBuffer("block_hit_1.mp3");
		instance.soundBufferMap[SoundTag::BlockHit2] = sf::SoundBuffer("block_hit_2.mp3");
		instance.soundBufferMap[SoundTag::BlockHit3] = sf::SoundBuffer("block_hit_3.mp3");
		instance.soundBufferMap[SoundTag::BlockHit4] = sf::SoundBuffer("block_hit_4.mp3");
		instance.soundBufferMap[SoundTag::BlockHit5] = sf::SoundBuffer("block_hit_5.mp3");
		instance.soundBufferMap[SoundTag::PaddleHit] = sf::SoundBuffer("paddle_hit.mp3");
		instance.soundBufferMap[SoundTag::BarrierHit] = sf::SoundBuffer("barrier_hit.mp3");

		for (const auto& [key, value] : instance.soundBufferMap) {
			instance.soundMap[key] = std::make_unique<sf::Sound>(value);
		}

		instance.initialized = true;
	}

	return instance;
}