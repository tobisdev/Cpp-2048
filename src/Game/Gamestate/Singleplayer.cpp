//
// Created by Tobias on 01.10.2024.
//

#include "Singleplayer.h"

void Singleplayer::update(float deltaTime, float speed) {
    _grid.update(deltaTime, speed);
}

void Singleplayer::render(sf::RenderWindow &window, sf::Font &font) {
    _grid.render(window, font);
}

void Singleplayer::handleEvents(sf::Event &event) {
    // Movement event
    Direction direction = None;

    if(event.key.code == sf::Keyboard::Key::A || event.key.code == sf::Keyboard::Key::Left){
        direction = Left;
    }
    if(event.key.code == sf::Keyboard::Key::S || event.key.code == sf::Keyboard::Key::Down){
        direction = Down;
    }
    if(event.key.code == sf::Keyboard::Key::D || event.key.code == sf::Keyboard::Key::Right){
        direction = Right;
    }
    if(event.key.code == sf::Keyboard::Key::W || event.key.code == sf::Keyboard::Key::Up){
        direction = Up;
    }

    _grid.move(direction);

    if(_grid.isGameOver()){
        std::cout << "You lost!\n============================\nYou got " << _grid.getSum() << " Points!\n\n";
        _grid = Grid(_grid.size());
    }
}
