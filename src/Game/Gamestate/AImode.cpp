//
// Created by Tobias on 01.10.2024.
//

#include "AImode.h"

AImode::AImode(int size, int AIs) {
    float min = 0.25f;
    float max = 0.85f;

    std::vector<int> topology = {
            size * size,
            6,
            4
    };
    std::vector<Activations> activations = {
            Sigmoid,
            Sigmoid
    };

    _agent = {AIs, topology, activations, min, max};
    _grids = {AIs, Grid(size)};
    _points = {AIs, 0};
}

void AImode::update(float deltaTime, float speed) {
    for (int i = 0; i < _agent.size(); ++i) {
        _grids[i]
    }
}

void AImode::render(sf::RenderWindow &window, sf::Font &font) {

}

void AImode::handleEvents(sf::Event &event) {

}
