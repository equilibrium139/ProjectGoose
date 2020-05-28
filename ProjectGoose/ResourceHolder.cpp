#include "ResourceHolder.h"

std::unordered_map<std::string, sf::Texture> ResourceHolder::textures;

sf::Texture& ResourceHolder::GetTexture(const std::string& path)
{
	auto pair = textures.find(path);
	if (pair != textures.end())
	{
		return pair->second;
	}
	else
	{
		auto& newTexture = textures[path];
		newTexture.loadFromFile(path);
		return newTexture;
	}
}
