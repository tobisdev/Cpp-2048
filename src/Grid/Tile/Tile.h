//
// Created by Tobias on 30.09.2024.
//

#ifndef INC_2048_TILE_H
#define INC_2048_TILE_H

#include <SFML/Graphics.hpp>

class Tile {
private:
    int _power;

    sf::Vector2f _currentPos;
    sf::Vector2f _targetPos;

    bool _isMerging = false;

public:
    Tile() = default;
    Tile(int power, sf::Vector2f &currentPos) : _power(power), _currentPos(currentPos), _targetPos(currentPos) {};

    [[nodiscard]] int power() {return this->_power;};
    [[nodiscard]] bool isMerging() {return this->_isMerging;};
    [[nodiscard]] sf::Vector2f &currentPos() {return this->_currentPos;};
    [[nodiscard]] sf::Vector2f &targetPos() {return this->_targetPos;};

    void power(int power) {this->_power = power;};
    void isMerging(bool isMerging) {this->_isMerging = isMerging;};
};


#endif //INC_2048_TILE_H
