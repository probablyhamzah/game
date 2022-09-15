#include <SFML/Graphics.hpp>
#include "PlayState.hpp"
#include "GameOverState.hpp"
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "globals.hpp"

int main()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(640, 352), "game");

    StateMachine* machine = new StateMachine();
    AssetManager* assets = new AssetManager();
    
    PlayState* play = new PlayState(window, machine, assets);
    GameOverState* gameover = new GameOverState(window, machine);
   
    std::map<int, State*> states;
    states[PLAY_STATE] = play;
    states[GAME_OVER_STATE] = gameover;
    machine->setStates(states);

    machine->change(PLAY_STATE); 
    sf::Time dt = sf::seconds(1.f/60.f);
    
    while (window->isOpen())
    {
        timeSinceLastFrame += clock.restart();
        while (timeSinceLastFrame > dt)
        {
            timeSinceLastFrame -= dt;
            machine->processInput();
            machine->update(dt);
            machine->render();
        }
    }
}
