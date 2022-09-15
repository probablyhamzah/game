#include "Entity.hpp"
#include <iostream>
Entity::Entity()
{
    m_direction = {2.f, 0.f};
    m_body.setScale(1.f, 1.f);
    m_frame = 0;
    m_orientation = 0.f;
    m_state = idle;
    m_gravity = 50;
    m_dy = -15;
    m_elapsedTime = sf::Time::Zero;
    m_involTime = sf::Time::Zero;
    m_isInvol = false;
    
    m_noOfFrames[idle] = 6;
    m_noOfFrames[run] = 6;
    m_noOfFrames[jump] = 6;
    m_noOfFrames[fall] = 6;
    m_noOfFrames[attack] = 3;

    m_hitbox.setSize(sf::Vector2f(20, 5));
    m_hitbox.setFillColor(sf::Color::Red);

    m_health = 5;
    
}

Entity::~Entity()
{
}

void Entity::Init(const sf::Texture &texture, const sf::Vector2f &position)
{
    m_body.setTexture(texture);
    m_body.setPosition(position);
}

void Entity::changeState(STATE state)
{
    if(state == jump)
        m_dy = -15;
    
    else if(state == fall)
        m_dy = 0;
    
    
    m_state = state;
    m_frame = 0;
}

void Entity::changeOrientation(float orientation)
{
    if(m_state != jump && m_state != fall)
    {
        m_orientation = orientation;
    
        if(orientation != 0.f)
            m_body.setScale(orientation, 1.f);
        
    }
}

void Entity::setTexture(const sf::Texture &texture)
{
    m_body.setTexture(texture);   
}

int Entity::getFrame()
{
    return m_frame;
}

STATE Entity::getState()
{
    return m_state;
}

bool Entity::IsOn(const sf::Sprite &other) const
{
    return other.getGlobalBounds().intersects(m_body.getGlobalBounds());
}

bool Entity::isHit(const sf::FloatRect &rect) const
{
    return rect.intersects(m_hitbox.getGlobalBounds());
}

sf::FloatRect Entity::getBounds()
{
    return m_body.getGlobalBounds();
}

sf::RectangleShape Entity::getHitbox()
{
    return m_hitbox;
}

void Entity::hit()
{
    if(!m_isInvol)
    {
        std::cout << m_health << '\n';
        --m_health;
        m_isInvol = true;
    }
}

bool Entity::isDead(const sf::Vector2u &bounds)
{
    float bodyX = m_body.getPosition().x, bodyY = m_body.getPosition().y;

    if(m_health == 0 || bodyX < 0 || bodyY < 0 || bodyX > bounds.x || bodyY > bounds.y)
        return true;
    else
        return false;
}

void Entity::update(sf::Time dt)
{
    m_elapsedTime += dt;

    // there's something lousy about this

    if(m_state != idle)
    {
        if(m_elapsedTime.asSeconds() > 0.1)
        {
            if(m_state == attack && m_frame == 2)
                changeState(idle);
                
            m_frame = (m_frame + 1) % m_noOfFrames[m_state];
            m_elapsedTime = sf::Time::Zero;
        }

        
        sf::Vector2f offset = m_hitboxOffset;//{(45 + std::min(int(m_orientation), 0) * -15) * m_orientation, 35};
        if(m_orientation == 1)
            offset = {45, 35};
        else if(m_orientation == -1)
            offset = {-60, 35};
        
        m_hitboxOffset = offset;
        m_hitbox.setPosition(offset + m_body.getPosition());
    }       

    if(m_state == jump || m_state == fall)
    {
        m_dy += 1;
        m_body.setPosition({m_body.getPosition().x + 6.f * m_orientation, m_body.getPosition().y + m_dy});

    }

    if(m_isInvol)
    {
        m_involTime += dt;
        if(m_involTime.asSeconds() > 1)
        {
            m_isInvol = false;
            m_involTime = sf::Time::Zero;
        }
    }
    
    m_body.setPosition(m_body.getPosition() + m_orientation * m_direction);
    
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_body);
    //target.draw(m_hitbox);
}


/*

jumping needs to be improved. patched it for now.
running is too slow. lag in the frame for some reason
jumping is extremely weird. too quick. too high.
 */
