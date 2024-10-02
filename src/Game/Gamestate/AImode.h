//
// Created by Tobias on 01.10.2024.
//

#ifndef INC_2048_AIMODE_H
#define INC_2048_AIMODE_H

#include "Gamestate.h"
#include "../../Grid/Grid.h"
#include "../../AI/Agent/Agent.h"

class AImode : public Gamestate {
private:
    Agent _agent;
    std::vector<Grid> _grids;
    std::vector<int> _points;
public:
    explicit AImode(int size, int AIs);
    void update(float deltaTime, float speed) override;
    void render(sf::RenderWindow &window, sf::Font &font) override;
    void handleEvents(sf::Event &event) override;
};


#endif //INC_2048_AIMODE_H
