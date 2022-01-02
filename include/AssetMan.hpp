#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Engine
{
class AssetMan
{
private:
    std::map<int, std::unique_ptr<sf::Texture>> m_textures;
    std::map<int, std::vector<std::unique_ptr<sf::Texture>>> m_playerTextures;
    std::map<int, std::unique_ptr<sf::Font>> m_fonts;

public:
    AssetMan();
    ~AssetMan();

    void AddTexture(int id, const std::string &filePath, bool wantRepeated = false);
    void AddPlayerTexture(int id, const std::vector<std::string> filePath);
    void AddFont(int id, const std::string &filePath);

    const sf::Texture &GetTexture(int id) const;
    const sf::Texture &GetPlayerTexture(int id, int frame) const;
    const sf::Font &GetFont(int id) const;
};
} // namespace Engine
