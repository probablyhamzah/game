#include <iostream>
#include "GameOverState.hpp"

GameOverState::GameOverState()
{
    window = NULL;
}

GameOverState::GameOverState(sf::RenderWindow* window, StateMachine* machine)
{
    this->window = window;
    this->machine = machine;
}

GameOverState::GameOverState(const GameOverState& state)
{
}

GameOverState::~GameOverState()
{
}

void GameOverState::enter(const State& state)
{
}

void GameOverState::exit()
{
}

void GameOverState::processInput()
{
}

void GameOverState::update(sf::Time dt)
{
}

void GameOverState::render()
{
}
