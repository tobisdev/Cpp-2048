//
// Created by Tobias on 01.10.2024.
//

#ifndef INC_2048_SINGLEPLAYER_H
#define INC_2048_SINGLEPLAYER_H

#include "Gamestate.h"
#include "../../Grid/Grid.h"

class Singleplayer : public Gamestate {
private:
    Grid _grid;
public:
    explicit Singleplayer(int size) : _grid(size) {};
    void update(float deltaTime, float speed) override;
    void render(sf::RenderWindow &window, sf::Font &font) override;
    void handleEvents(sf::Event &event) override;
};


#endif //INC_2048_SINGLEPLAYER_H
