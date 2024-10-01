//
// Created by Tobias on 01.10.2024.
//

#ifndef INC_2048_GAMESTATE_H
#define INC_2048_GAMESTATE_H

#include "SFML/Graphics.hpp"

class Gamestate {
private:

public:
    virtual void update(float deltaTime, float speed) = 0;
    virtual void render(sf::RenderWindow &window, sf::Font &font) = 0;
    virtual void handleEvents(sf::Event &event) = 0;
};


#endif //INC_2048_GAMESTATE_H
