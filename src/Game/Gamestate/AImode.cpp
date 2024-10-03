//
// Created by Tobias on 01.10.2024.
//

#include "AImode.h"

AImode::AImode(int size, int AIs) {
    float min = -0.85f;
    float max = 0.85f;

    std::vector<int> topology = {
            size * size,
            6,
            4
    };
    std::vector<Activations> activations = {
            LeakyReLU,
            LeakyReLU,
            LeakyReLU
    };

    _agent = {AIs, topology, activations, min, max};
    _grids.reserve(AIs);
    for (int i = 0; i < AIs; ++i) {
        _grids.emplace_back(size);
    }
    _points = std::vector<float>(AIs, 0.0f);
}

void AImode::update(float deltaTime, float speed) {

    if(_move > _maxMove){

        for (int i = 0; i < _points.size(); ++i) {
            _points[i] = _grids[i].getEmptyTiles() + _grids[i].calculateMonotonicity() + _grids[i].evaluateCornerClustering() + 5.0f * _grids[i].getBiggestTile();
            //std::cout << "Gen: " << _generation << "\tAI: " << i << "\tPoints: "<< _points[i] << "\n";
        }

        // Report
        std::cout << "\nReport for gen " << _generation << ":\n=========================================\n";
        auto maxIt = std::max_element(_points.begin(), _points.end());
        int maxIndex = std::distance(_points.begin(), maxIt);
        std::cout << "Best AI: " << maxIndex << " with " << _points[maxIndex] << " points!\n";
        std::cout << "That is " << (int)(100.0f * (_points[maxIndex] / _previousPoints - 1)) << "% better than before!\n";
        std::cout << "=========================================\n";

        _previousPoints = _points[maxIndex];

        _agent.breed(_points, _agent.size() / 5, 100, 0.1f);
        _move = 0;
        _points = std::vector<float>(_points.size(), 0.0f);

        int size = _grids[0].size();
        _grids.clear();
        _grids.reserve(_points.size());
        for (int i = 0; i < _points.size(); ++i) {
            _grids.emplace_back(size);
        }
        _generation++;
        _maxMove += 4;
    }

    for (int i = 0; i < _agent.size(); ++i) {

        if(_points[i] == 0){

            std::vector<float> values = _grids[i].getLinearVector();

            std::vector<float> move = _agent[i].feedForward(values);

            auto maxIt = std::max_element(move.begin(), move.end());
            int maxIndex = std::distance(move.begin(), maxIt);

            switch (maxIndex) {
                case 0:
                    _grids[i].move(Up);
                    break;
                case 1:
                    _grids[i].move(Down);
                    break;
                case 2:
                    _grids[i].move(Left);
                    break;
                case 3:
                    _grids[i].move(Right);
                    break;
            }

            if (_grids[i].isGameOver()){
                _points[i] = -1;
            }
        }

    }

    _move++;

    _grids[0].update(deltaTime, speed);
}

void AImode::render(sf::RenderWindow &window, sf::Font &font) {
    if(_grids.size() > 0){
        _grids[0].render(window, font);
    }
}

void AImode::handleEvents(sf::Event &event) {

}
