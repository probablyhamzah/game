#include "PlayState.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>
#include <array>
#include <iostream>
#include <vector>


PlayState::PlayState(std::shared_ptr<Context> &context)
    : m_context(context),
      m_score(0),
      //m_entityDirection({16.f, 0.f}),
      m_elapsedTime(sf::Time::Zero)
{
}

PlayState::~PlayState()
{
}

void PlayState::Init()
{
    m_context->m_assets->AddTexture(WALL, "assets/textures/wall.png", true);
    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");
    
    m_context->m_assets->AddPlayerTexture(NINJA, {
            "assets/textures/2x/run_0.png",
            "assets/textures/2x/run_1.png",
            "assets/textures/2x/run_2.png",
            "assets/textures/2x/run_3.png",
            "assets/textures/2x/run_4.png",
            "assets/textures/2x/run_5.png"
        });

    m_context->m_assets->AddPlayerTexture(ATTACK, {
            "assets/textures/2x/attack_0.png",
            "assets/textures/2x/attack_1.png",
            "assets/textures/2x/attack_2.png"
        });
    
        
    m_block.Init(m_context->m_assets->GetTexture(WALL), {0, 0, 360, 60});


    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0, 200); 

    for(int i = 0; i < 2; i++)
    {
        srand(time(nullptr));

        m_entities[i].Init(m_context->m_assets->GetPlayerTexture(NINJA, 0), {float(distr(gen)), 30});
        
        m_entities[i].changeState(fall);
        std::uniform_int_distribution<> distr(400, 600); 

    }

}

void PlayState::ProcessInput()
{
    
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            float orientation= 0.f;
            switch (event.key.code)
            {
                // shit ton of patching done with respect to changing states. improve this
            case sf::Keyboard::Left:
                orientation = -1.f;
                if(m_entities[0].getState() == idle)
                    m_entities[0].changeState(run);
                m_entities[0].changeOrientation(orientation);
                break;
            case sf::Keyboard::Right:
                orientation = 1.f;
                if(m_entities[0].getState() == idle)
                    m_entities[0].changeState(run);
                m_entities[0].changeOrientation(orientation);
                break;
            case sf::Keyboard::Up:
                m_entities[0].changeState(jump);
                break;
            case sf::Keyboard::LShift:
                m_entities[0].changeState(attack);
                break;

            case sf::Keyboard::A:
                orientation = -1.f;
                if(m_entities[1].getState() == idle)
                    m_entities[1].changeState(run);
                m_entities[1].changeOrientation(orientation);
                break;
            case sf::Keyboard::D:
                orientation = 1.f;
                if(m_entities[1].getState() == idle)
                    m_entities[1].changeState(run);
                m_entities[1].changeOrientation(orientation);
                break;
            case sf::Keyboard::W:
                m_entities[1].changeState(jump);
                break;
            case sf::Keyboard::RShift:
                m_entities[1].changeState(attack);
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
                
                m_entities[0].changeOrientation(0.f);
                if(m_entities[0].getState() == run)
                    m_entities[0].changeState(idle);
                break;
                
            case sf::Keyboard::A:
            case sf::Keyboard::D:
                
                m_entities[1].changeOrientation(0.f);
                if(m_entities[1].getState() == run)
                    m_entities[1].changeState(idle);
                break;
                
            default:
                break;
                
            }
                
            
        }
    }
}

void PlayState::Update(sf::Time deltaTime)
{
    m_elapsedTime += deltaTime;

    for(int i = 0; i < 2; i++)
    {
    
        m_entities[i].update(deltaTime);
    
        if(m_entities[i].getState() != attack)
            m_entities[i].setTexture(m_context->m_assets->GetPlayerTexture(NINJA, m_entities[i].getFrame()));
        else
            m_entities[i].setTexture(m_context->m_assets->GetPlayerTexture(ATTACK, m_entities[i].getFrame()));


        // improve this
        bool isOn = false;
        if(m_block.isColliding(m_entities[i].getBounds()))
        {
            if(m_entities[i].getState() == fall || m_entities[i].getState() == jump)
                m_entities[i].changeState(idle);
            isOn = true;
        }

        //do something about this
    
        if(!isOn && m_entities[i].getState() != fall && m_entities[i].getState() != jump && m_entities[i].getState() != idle)
            m_entities[i].changeState(fall);

        if(m_entities[i].isDead(m_context->m_window->getSize()))
        {
            m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
            break;
        }
    }


    if(m_entities[0].getState() == attack && m_entities[0].isHit(m_entities[1].getBounds()))
    {
        m_entities[1].hit();
    }
    else if(m_entities[1].getState() == attack && m_entities[1].isHit(m_entities[0].getBounds()))
    {
        m_entities[0].hit();
    }


    
}

void PlayState::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_block);

    for(int i = 0; i < 2; i++)
        m_context->m_window->draw(m_entities[i]);
    
    m_context->m_window->display();
}

void PlayState::Pause()
{
    m_isPaused = true;
}

void PlayState::Start()
{
    m_isPaused = false;
}
