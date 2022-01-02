#pragma once

#include <memory>
#include <array>
#include <vector>
#include <random>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Game.hpp"
#include "State.hpp"
#include "Entity.hpp"
#include "Block.hpp"

class PlayState : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;

    Entity m_entities[2];
    
    Block m_block;
    int m_score;

    //sf::Vector2f m_entityDirection;
    sf::Time m_elapsedTime;
    //sf::RectangleShape m_testbox;
    
    bool m_isPaused;

public:
    PlayState(std::shared_ptr<Context> &context);
    ~PlayState();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;
};
