#include "Block.hpp"

Block::Block()
{
}

Block::~Block()
{
}

void Block::Init(const sf::Texture &texture, const sf::IntRect &rectangle)
{
    m_body.setTexture(texture);
    m_body.setTextureRect(rectangle);
    m_body.setPosition({30,190});
}

sf::Sprite Block::getBody()
{
    return m_body;
}


bool Block::isColliding(const sf::FloatRect &rect) const
{
    return rect.intersects(m_body.getGlobalBounds());
}


void Block::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    
    target.draw(m_body);
    
}
