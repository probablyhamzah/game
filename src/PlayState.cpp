#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <vector>
#include <random>
#include "PlayState.hpp"

PlayState::PlayState()
{
    window = NULL;
    machine = NULL;
}

PlayState::PlayState(sf::RenderWindow* window, StateMachine* machine, AssetManager* assets)
{
    this->window = window;
    this->machine = machine;
    this->assets = assets;
    
    score = 0;
    elapsedTime = sf::Time::Zero;
    
    assets->setTexture(WALL, "assets/textures/wall.png", true);
    
    assets->setPlayerTexture(NINJA, {
            "assets/textures/2x/run_0.png",
            "assets/textures/2x/run_1.png",
            "assets/textures/2x/run_2.png",
            "assets/textures/2x/run_3.png",
            "assets/textures/2x/run_4.png",
            "assets/textures/2x/run_5.png"
        });

    assets->setPlayerTexture(ATTACK, {
            "assets/textures/2x/attack_0.png",
            "assets/textures/2x/attack_1.png",
            "assets/textures/2x/attack_2.png"
        });
    
        
    block.Init(assets->getTexture(WALL), {0, 0, 360, 60});


    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0, 200); 

    for(int i = 0; i < 2; i++)
    {
        srand(time(nullptr));

        entities[i].Init(assets->getPlayerTexture(NINJA, 0), {float(distr(gen)), 30});
        
        entities[i].changeState(fall);
        std::uniform_int_distribution<> distr(400, 600); 

    }
}

PlayState::PlayState(const PlayState& state)
{
    std::cout << "playstate copy constructor\n";
}

PlayState::~PlayState()
{
    std::cout << "playstate destructor\n";
}

void PlayState::processInput()
{
    if (window == NULL)
        return;
    
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            float orientation= 0.f;
            switch (event.key.code)
            {
                // shit ton of patching done with respect to changing states. improve this
            case sf::Keyboard::Left:
                orientation = -1.f;
                if(entities[0].getState() == idle)
                    entities[0].changeState(run);
                entities[0].changeOrientation(orientation);
                break;
            case sf::Keyboard::Right:
                orientation = 1.f;
                if(entities[0].getState() == idle)
                    entities[0].changeState(run);
                entities[0].changeOrientation(orientation);
                break;
            case sf::Keyboard::Up:
                entities[0].changeState(jump);
                break;
            case sf::Keyboard::LShift:
                entities[0].changeState(attack);
                break;

            case sf::Keyboard::A:
                orientation = -1.f;
                if(entities[1].getState() == idle)
                    entities[1].changeState(run);
                entities[1].changeOrientation(orientation);
                break;
            case sf::Keyboard::D:
                orientation = 1.f;
                if(entities[1].getState() == idle)
                    entities[1].changeState(run);
                entities[1].changeOrientation(orientation);
                break;
            case sf::Keyboard::W:
                entities[1].changeState(jump);
                break;
            case sf::Keyboard::RShift:
                entities[1].changeState(attack);
                break;

            default:
                break;
            }

        }
        else if(event.type == sf::Event::KeyReleased)
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Left:
            case sf::Keyboard::Right:
                
                entities[0].changeOrientation(0.f);
                if(entities[0].getState() == run)
                    entities[0].changeState(idle);
                break;
                
            case sf::Keyboard::A:
            case sf::Keyboard::D:
                
                entities[1].changeOrientation(0.f);
                if(entities[1].getState() == run)
                    entities[1].changeState(idle);
                break;
                
            default:
                break;
                
            }
                
            
        }
    }
}



void PlayState::update(sf::Time dt)
{
    elapsedTime += dt;

    for(int i = 0; i < 2; i++)
    {
    
        entities[i].update(dt);
    
        if(entities[i].getState() != attack)
            entities[i].setTexture(assets->getPlayerTexture(NINJA, entities[i].getFrame()));
        else
            entities[i].setTexture(assets->getPlayerTexture(ATTACK, entities[i].getFrame()));


        // improve this
        bool isOn = false;
        if(block.isColliding(entities[i].getBounds()))
        {
            if(entities[i].getState() == fall || entities[i].getState() == jump)
                entities[i].changeState(idle);
            isOn = true;
        }

        //do something about this
    
        if(!isOn && entities[i].getState() != fall && entities[i].getState() != jump && entities[i].getState() != idle)
            entities[i].changeState(fall);

        if(entities[i].isDead(window->getSize()))
        {
            machine->change(GAME_OVER_STATE);
        }
    }


    if(entities[0].getState() == attack && entities[0].isHit(entities[1].getBounds()))
    {
        entities[1].hit();
    }
    else if(entities[1].getState() == attack && entities[1].isHit(entities[0].getBounds()))
    {
        entities[0].hit();
    }
}

void PlayState::render()
{
    window->clear();
    window->draw(block);

    for(int i = 0; i < 2; i++)
        window->draw(entities[i]);
    
    window->display();
}
