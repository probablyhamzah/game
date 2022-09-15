#include "StateMachine.hpp"
#include <iostream>

StateMachine::StateMachine()
{
}

void StateMachine::setStates(std::map<int, State*> states)
{
    this->states = states;
}

void StateMachine::change(int stateName, State* state)
{
    if (state != nullptr)
    {
        if (
            this->states.find(stateName) != this->states.end() &&
            this->states[stateName] != nullptr
            )
            delete this->states[stateName];
        
        this->states[stateName] = state;
    }
    
    this->current = stateName;
}

void StateMachine::processInput()
{
    this->states[current]->processInput();
}

void StateMachine::update(sf::Time dt)
{
    this->states[current]->update(dt);
}

void StateMachine::render()
{
    this->states[current]->render();
}
