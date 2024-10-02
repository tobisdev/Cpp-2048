//
// Created by Tobias on 01.10.2024.
//

#ifndef INC_2048_MENU_H
#define INC_2048_MENU_H

#include "Gamestate.h"
#include <SFML/Graphics.hpp>

class Menu : public Gamestate {
private:
    std::vector<std::string> buttonLabels = {"Singleplayer", "Computer", "Exit"};
    std::vector<sf::Text> buttons;
public:
    explicit Menu();
    void update(float deltaTime, float speed) override;
    void render(sf::RenderWindow &window, sf::Font &font) override;
    void handleEvents(sf::Event &event) override;
};


#endif //INC_2048_MENU_H
