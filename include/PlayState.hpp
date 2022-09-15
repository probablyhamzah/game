#pragma once

#include "State.hpp"
#include "globals.hpp"
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "Entity.hpp"
#include "Block.hpp"

#include <SFML/Graphics.hpp>

class PlayState : public State
{
private:
    sf::RenderWindow* window;
    StateMachine* machine;
    AssetManager* assets;
    
    int score;
    Entity entities[2];
    Block block;
    sf::Time elapsedTime;
    
public:
    PlayState();
    PlayState(sf::RenderWindow* window, StateMachine* machine, AssetManager* assets);
    PlayState(const PlayState& state);
    ~PlayState();


    void processInput();
    void update(sf::Time dt);
    void render();
};
