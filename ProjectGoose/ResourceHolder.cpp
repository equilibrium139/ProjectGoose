#include "ResourceHolder.h"


sf::Texture& ResourceHolder::GetTexture(const std::string& path)
{
	// not class member because it might not be initialized the first time this function is called
	static std::unordered_map<std::string, sf::Texture> textures;

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
