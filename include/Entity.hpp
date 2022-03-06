#pragma once

#include <map>
#include <algorithm>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>

enum State
{
    idle,
    run,
    jump,
    fall,
    attack
};

class Entity : public sf::Drawable
{
private:
    sf::Sprite m_body;
    sf::Vector2f m_direction;
    int m_frame;
    float m_orientation;
    int m_dy;
    State m_state;
    int m_gravity;
    sf::Time m_elapsedTime;
    sf::Time m_involTime;
    bool m_isInvol;
    sf::RectangleShape m_hitbox;
    sf::Vector2f m_hitboxOffset;
    int m_health;
    
    std::map<State, int> m_noOfFrames;

public:
    Entity();
    ~Entity();

    void Init(const sf::Texture &texture, const sf::Vector2f &position);
    int getFrame();
    void setTexture(const sf::Texture &texture);
    void update(sf::Time dt);
    void changeOrientation(float orientation);
    State getState();
    sf::RectangleShape getHitbox();
    sf::FloatRect getBounds();
    void changeState(State state);
    bool IsOn(const sf::Sprite &other) const;
    bool isHit(const sf::FloatRect &rect) const;
    void hit();
    bool isDead(const sf::Vector2u &bounds);
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
