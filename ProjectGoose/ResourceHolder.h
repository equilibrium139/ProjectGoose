#pragma once

#include <unordered_map>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class ResourceHolder
{
public:
	ResourceHolder() = delete;
	static sf::Texture& GetTexture(const std::string& path);
	static sf::SoundBuffer& GetSoundBuffer(const std::string& path);
};