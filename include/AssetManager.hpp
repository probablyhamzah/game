#pragma once

#include <string>
#include <vector>
#include <map>

#include <SFML/Graphics/Texture.hpp>

class AssetManager
{
private:
    std::map<int, sf::Texture*> textures;
    std::map<int, std::vector<sf::Texture*>> playerTextures;
public:
    AssetManager();
    ~AssetManager();

    void setTexture(int id, const std::string file, bool repeat = false);
    void setPlayerTexture(int id, const std::vector<std::string> files);

    
    const sf::Texture& getTexture(int id) const;
    const sf::Texture& getPlayerTexture(int id, int frame) const;
};
