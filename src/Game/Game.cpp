//
// Created by Tobias on 30.09.2024.
//

#include "Game.h"

Game::Game(sf::Vector2i size, std::string title) :
sf::RenderWindow(sf::VideoMode(size.x, size.y), title) {
    // set current time
    _currentTime = std::chrono::high_resolution_clock::now();
    _previousTime = _currentTime;

    // FONT
    if (!_globalFont.loadFromFile("../resources/fonts/Roboto.ttf")) {
        return;
    }
}

void Game::update() {
    // time calculations
    _currentTime = std::chrono::high_resolution_clock::now();
    _deltaTime = std::chrono::duration<float>(_currentTime - _previousTime).count();
    _previousTime = _currentTime;
    _framesPerSecond = 1.0 / _deltaTime;

    // grab all SFML-events
    sf::Event event;
    while (this->pollEvent(event)) {

        switch (event.type) {
            case sf::Event::Closed:
                this->close();
                break;
            case sf::Event::Resized:
                // catch the resize events
                if (event.type == sf::Event::Resized)
                {
                    // update the view to the new size of the window
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    this->setView(sf::View(visibleArea));
                }
            case sf::Event::KeyPressed:
            {
                // Send events to gamestate
                gamestate->handleEvents(event);
            }
            default:
                break;
        }
    }

    // Update gamestate
    gamestate->update(_deltaTime, 45.0f);
}

void Game::render() {
    // Clear the view
    this->clear();

    // render gamestate
    gamestate->render(*this, _globalFont);

    // fps display
    sf::Text text;
    text.setFont(_globalFont); // Set the font
    text.setString("FPS: " + std::to_string((int)_framesPerSecond));
    float mult = 1; //_originalWidth / this->getSize().x;
    text.setCharacterSize(14 * mult);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);
    this->draw(text);
    text.setString("FrameTime: " + std::to_string((int)(_deltaTime * 1000.0f)) + "." + std::to_string((int)(_deltaTime * 1000.0f * 10) % 10) + "ms");
    text.setPosition(10, 30);
    this->draw(text);

    // Display the view
    this->display();
}