#pragma once

#include "State.hpp"
#include <string>
#include <map>


class StateMachine
{
private:
    std::map<int, State*> states;
    int current;
public:
    StateMachine();
    void setStates(std::map<int, State*> states);
    void change(int stateName, State* state = nullptr);
    void processInput();
    void update(sf::Time dt);
    void render();
};
