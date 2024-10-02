//
// Created by Tobias on 01.10.2024.
//

#include "Menu.h"

Menu::Menu() {
    for (int i = 0; i < buttonLabels.size(); i++) {
        sf::Text button;
        button.setString(buttonLabels[i]);
        button.setFillColor(sf::Color::White);
        button.setStyle(sf::Text::Bold);
        buttons.push_back(button);
    }
}

void Menu::render(sf::RenderWindow &window, sf::Font &font) {
    // Get window size for scaling
    sf::Vector2u windowSize = window.getSize();

    // Scaling factors based on window size
    float scaleX = windowSize.x / 800.0f;
    float scaleY = windowSize.y / 600.0f;

    // Create background with gradient effect (or texture for a fancy look)
    sf::RectangleShape background(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));
    background.setFillColor(sf::Color(50, 50, 150)); // Dark blue

    float buttonSpacing = 60.0f * scaleY;
    float buttonHeight = 50.0f * scaleY;
    float buttonWidth = 200.0f * scaleX;
    float startX = (windowSize.x - buttonWidth) / 2.0f;
    float startY = windowSize.y / 3.0f;

    for (int i = 0; i < buttons.size(); i++) {
        sf::Text &button = buttons[i];
        button.setFont(font);
        button.setString(buttonLabels[i]);
        button.setCharacterSize(static_cast<unsigned int>(36 * scaleY)); // Scaled text size
        button.setFillColor(sf::Color::White);
        button.setStyle(sf::Text::Bold);

        // Center button horizontally and place it vertically with spacing
        button.setPosition(startX, startY + i * buttonSpacing);
    }

    // Draw everything
    window.draw(background);
    for (auto &button : buttons) {
        window.draw(button);
    }
}

void Menu::handleEvents(sf::Event &event) {

}