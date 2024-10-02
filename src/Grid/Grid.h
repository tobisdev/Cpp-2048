//
// Created by Tobias on 30.09.2024.
//

#ifndef INC_2048_GRID_H
#define INC_2048_GRID_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include "Tile/Tile.h"

enum Direction {None, Up, Down, Left, Right };

class Grid {
private:
    std::vector<std::vector<Tile*>> _tiles;
    int _size;

public:
    Grid() = default;
    Grid(int size);
    ~Grid();

    void move(Direction direction);

    void update(float deltaTime, float speed);
    void render(sf::RenderWindow &window, sf::Font &font);

    void placeRandomNumber();

    bool isGameOver();

    int getSum();
    int getBiggestTile();
    int getEmptyTiles();
    std::vector<float> getLinearVector();

    [[nodiscard]] int size() {return this->_size;};
    [[nodiscard]] std::vector<Tile *> &operator[] (int i) {return this->_tiles[i];}
};


#endif //INC_2048_GRID_H
