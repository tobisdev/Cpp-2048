//
// Created by Tobias on 30.09.2024.
//

#include "Grid.h"

Grid::Grid(int size) : _size(size) {
    _tiles.resize(size, std::vector<Tile*>(size, nullptr));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            _tiles[i][j] = nullptr;
        }
    }

    placeRandomNumber();
}

Grid::~Grid() {
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if(_tiles[i][j]){
                delete _tiles[i][j];
                _tiles[i][j] = nullptr;
            }
        }
    }
}

void Grid::placeRandomNumber() {
    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_int_distribution<std::mt19937::result_type> distPos(0,_size - 1);
    std::uniform_int_distribution<std::mt19937::result_type> distNum(0,10);

    int randX = distPos(rng);
    int randY = distPos(rng);

    int cnt = 0;

    while(_tiles[randX][randY] != nullptr){
        randX = distPos(rng);
        randY = distPos(rng);

        if (cnt > 10){
            return;
        }

        cnt++;
    }

    sf::Vector2f pos(randX, randY);
    int num = distNum(rng);
    _tiles[randX][randY] = new Tile((num > 9) ? 2 : 1, pos);
}

void Grid::move(Direction direction) {
    if(direction == None){
        return;
    }

    int offsetX = (direction == Left) ? -1 : (direction == Right) ? +1 : 0;
    int offsetY = (direction == Up) ? -1 : (direction == Down) ? +1 : 0;

    int maxX = (direction == Left) ? 0 : (direction == Right) ? _size - 1 : _size;
    int maxY = (direction == Up) ? 0 : (direction == Down) ? _size - 1 : _size;
    int minX = (direction == Left) ? _size - 1 : 0;
    int minY = (direction == Up) ? _size - 1 : 0;

    int stepX = (direction == Left) ? -1 : +1;
    int stepY = (direction == Up) ? -1 : +1;

        for (int i = minX; i != maxX; i += stepX) {
            for (int j = minY; j != maxY; j += stepY) {

                int newI = i + offsetX;
                int newJ = j + offsetY;

                if (_tiles[i][j] != nullptr) {
                    if (_tiles[newI][newJ] == nullptr) {
                        _tiles[i][j]->targetPos() = {(float) newI, (float) newJ};
                        _tiles[newI][newJ] = _tiles[i][j];
                        _tiles[i][j] = nullptr;
                    } else if (_tiles[newI][newJ]->power() == _tiles[i][j]->power()) {
                        _tiles[i][j]->power(_tiles[i][j]->power() + 1);
                        _tiles[i][j]->targetPos() = _tiles[newI][newJ]->targetPos();
                        delete _tiles[newI][newJ];
                        _tiles[newI][newJ] = _tiles[i][j];
                        _tiles[i][j] = nullptr;
                    }
                }
            }
        }

    placeRandomNumber();
}

bool Grid::isGameOver() {
    // Check for empty tiles
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if (_tiles[i][j] == nullptr) {
                return false;
            }
        }
    }

    // Check if the current tile can be merged with adjacent tiles
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if (i > 0 && _tiles[i][j]->power() == _tiles[i - 1][j]->power()) {
                return false;
            }
            if (i < _size - 1 && _tiles[i][j]->power() == _tiles[i + 1][j]->power()) {
                return false;
            }
            if (j > 0 && _tiles[i][j]->power() == _tiles[i][j - 1]->power()) {
                return false;
            }
            if (j < _size - 1 && _tiles[i][j]->power() == _tiles[i][j + 1]->power()) {
                return false;
            }
        }
    }
    return true;
}

void Grid::update(float deltaTime, float speed) {
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            Tile *tile = _tiles[i][j];
            if(tile != nullptr){
                sf::Vector2f &pos = tile->currentPos();
                sf::Vector2f &dest = tile->targetPos();

                pos -= (pos - dest) * speed * deltaTime;
            }
        }
    }
}

int Grid::getSum() {
    int sum = 0;
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if(_tiles[i][j] != nullptr){
                sum += pow(2, _tiles[i][j]->power());
            }
        }
    }
    return sum;
}

void Grid::render(sf::RenderWindow &window, sf::Font &font) {
    sf::RectangleShape rect;

    float width = window.getSize().x;
    float height = window.getSize().y;

    float displaySize = (width > height) ? height : width;

    float borderSize = displaySize / 100;

    sf::Vector2f center(width / 2 - displaySize / 2, height / 2 - displaySize / 2);

    // Background
    rect.setPosition(center);
    rect.setSize({displaySize, displaySize});
    rect.setFillColor({30, 30, 30});

    window.draw(rect);

    // Border
    rect.setPosition({center.x + borderSize, center.y + borderSize});
    rect.setSize({displaySize - 2 * borderSize, displaySize - 2 * borderSize});
    rect.setFillColor({80, 80, 80});

    window.draw(rect);

    // Boxes
    float boxSize = (displaySize - 2 * borderSize) / _size;
    sf::Vector2f boxPosition(center.x + borderSize, center.y + borderSize);

    sf::Text text;
    text.setFont(font); // Set the font
    text.setCharacterSize(10 * borderSize);
    text.setFillColor(sf::Color::White);

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            Tile *tile = _tiles[i][j];
            
            if(tile != nullptr){
                // Outline
                rect.setSize({boxSize, boxSize});
                rect.setPosition(boxPosition.x + tile->currentPos().x * boxSize, boxPosition.y + tile->currentPos().y * boxSize);
                rect.setFillColor({100, 100, 100});
                window.draw(rect);

                // Inner
                rect.setSize({boxSize - 2 * borderSize, boxSize - 2 * borderSize});
                rect.setPosition(boxPosition.x + tile->currentPos().x * boxSize + borderSize, boxPosition.y + tile->currentPos().y * boxSize + borderSize);
                switch (tile->power()) {
                    case 1:
                        rect.setFillColor(sf::Color(238, 228, 218)); // light beige for 2
                        break;
                    case 2:
                        rect.setFillColor(sf::Color(237, 224, 200)); // slightly darker beige for 4
                        break;
                    case 3:
                        rect.setFillColor(sf::Color(242, 177, 121)); // soft orange for 8
                        break;
                    case 4:
                        rect.setFillColor(sf::Color(245, 149, 99));  // deeper orange for 16
                        break;
                    case 5:
                        rect.setFillColor(sf::Color(246, 124, 95));  // reddish-orange for 32
                        break;
                    case 6:
                        rect.setFillColor(sf::Color(246, 94, 59));   // red-orange for 64
                        break;
                    case 7:
                        rect.setFillColor(sf::Color(237, 207, 114)); // golden-yellow for 128
                        break;
                    case 8:
                        rect.setFillColor(sf::Color(237, 204, 97));  // slightly deeper yellow for 256
                        break;
                    case 9:
                        rect.setFillColor(sf::Color(237, 200, 80));  // warm yellow for 512
                        break;
                    case 10:
                        rect.setFillColor(sf::Color(237, 197, 63));  // darker golden yellow for 1024
                        break;
                    case 11:
                        rect.setFillColor(sf::Color(237, 194, 46));  // golden orange for 2048
                        break;
                    default:
                        rect.setFillColor(sf::Color(140, 0, 0));     // dark red for 4096 and beyond
                        break;
                }
                window.draw(rect);

                text.setString(std::to_string((int)powf(2, tile->power())));
                sf::Vector2f textSize = text.getGlobalBounds().getSize();
                text.setPosition(boxPosition.x + tile->currentPos().x * boxSize - textSize.x / 2 + 0.49f * boxSize, boxPosition.y + tile->currentPos().y * boxSize - textSize.y / 2 + 0.4f * boxSize);
                window.draw(text);
            }
        }
    }
}

int Grid::getEmptyTiles() {
    int empty = 0;

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if(_tiles[i][j] == nullptr){
                empty++;
            }
        }
    }

    return empty;
}

std::vector<float> Grid::getLinearVector() {
    std::vector<float> vect(_size * _size, 0.0f);

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if(_tiles[i][j] != nullptr){
                vect[j + _size * i] = 1.0f / _tiles[i][j]->power();
            }
        }
    }

    return vect;
}

int Grid::getBiggestTile() {
    int biggest = 0;

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if(_tiles[i][j] != nullptr){
                biggest = (_tiles[i][j]->power() > biggest) ? _tiles[i][j]->power() : biggest;
            }
        }
    }

    return biggest;
}

float Grid::evaluateCornerClustering() {
    float cornerReward = 0.0f;;

    // Corner positions
    std::vector<std::pair<int, int>> corners = {
            {0, 0}, {0, _size - 1}, {_size - 1, 0}, {_size - 1, _size - 1}
    };

    for (const auto &corner : corners) {
        if(_tiles[corner.first][corner.second] != nullptr){
            cornerReward += 2.0f * _tiles[corner.first][corner.second]->power();
        }
    }

    return cornerReward;
}

float Grid::calculateMonotonicity() {
    float monotonicity = 0.0f;

    // Check rows and columns for monotonicity
    for (int row = 0; row < _size; ++row) {
        for (int col = 0; col < _size - 1; ++col) {
            // Monotonic in rows
            if (_tiles[row][col] != nullptr && _tiles[row][col + 1] != nullptr && _tiles[row][col]->power() >= _tiles[row][col + 1]->power()) {
                monotonicity += 1.0f;
            }
            // Monotonic in columns
            if (_tiles[col + 1][row] != nullptr && _tiles[col][row] != nullptr && _tiles[col][row]->power() >= _tiles[col + 1][row]->power()) {
                monotonicity += 1.0f;
            }
        }
    }

    return monotonicity;
}