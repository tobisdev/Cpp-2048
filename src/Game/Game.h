//
// Created by Tobias on 30.09.2024.
//

#ifndef INC_2048_GAME_H
#define INC_2048_GAME_H

#include <SFML/Graphics.hpp>
#include <chrono>

#include "../Grid/Grid.h"
#include "Gamestate/Gamestate.h"
#include "Gamestate/Singleplayer.h"
#include "Gamestate/AImode.h"
#include "Gamestate/Menu.h"

class Game : public sf::RenderWindow {
private:
    float _deltaTime = 0.0;
    float _framesPerSecond = 0.0;
    std::chrono::time_point<std::chrono::system_clock> _currentTime;
    std::chrono::time_point<std::chrono::system_clock> _previousTime;

    sf::Font _globalFont;
    //Gamestate *gamestate = new Singleplayer(4);
    Gamestate *gamestate = new AImode(4, 200);
public:
    Game();
    Game(sf::Vector2i size, std::string title);

    [[nodiscard]] float deltaTime() const {return this->_deltaTime;};
    [[nodiscard]] float fps() const {return this->_framesPerSecond;};
    [[nodiscard]] sf::Font &font() {return this->_globalFont;};

    void update();
    void render();
};


#endif //INC_2048_GAME_H
