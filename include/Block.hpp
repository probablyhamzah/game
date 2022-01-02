#pragma once

#include <list>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Rect.hpp>

class Block : public sf::Drawable
{
private:
    sf::Sprite m_body;
    
public:
    Block();
    ~Block();

    void Init(const sf::Texture &texture, const sf::IntRect &rectangle);
    sf::Sprite getBody();
    bool isColliding(const sf::FloatRect &rect) const;
    //bool IsOn(const sf::Sprite &other) const;
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
