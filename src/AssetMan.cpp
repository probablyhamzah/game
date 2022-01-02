#include "AssetMan.hpp"

Engine::AssetMan::AssetMan()
{
}

Engine::AssetMan::~AssetMan()
{
}

void Engine::AssetMan::AddTexture(int id, const std::string &filePath, bool wantRepeated)
{
    auto texture = std::make_unique<sf::Texture>();

    if(texture->loadFromFile(filePath))
    {
        texture->setRepeated(wantRepeated);
        m_textures[id] = std::move(texture);
    }
}

void Engine::AssetMan::AddPlayerTexture(int id, const std::vector<std::string> filePath)
{
    //std::map<int, std::unique_ptr<sf::Texture>[6]> player_textures;
    for(int i = 0; i < int(filePath.size()); i++)
    {
        auto texture = std::make_unique<sf::Texture>();

        if(texture->loadFromFile(filePath[i]))
        {
            m_playerTextures[id].push_back(std::move(texture));
        }
    }
}


void Engine::AssetMan::AddFont(int id, const std::string &filePath)
{
    auto font = std::make_unique<sf::Font>();

    if(font->loadFromFile(filePath))
    {
        m_fonts[id] = std::move(font);
    }
}

const sf::Texture &Engine::AssetMan::GetTexture(int id) const
{
    return *(m_textures.at(id).get());
}

const sf::Texture &Engine::AssetMan::GetPlayerTexture(int id, int frame) const
{
    return *(m_playerTextures.at(id)[frame].get());
}

const sf::Font &Engine::AssetMan::GetFont(int id) const
{
    return *(m_fonts.at(id).get());
}
