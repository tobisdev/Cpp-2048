#include <iostream>
#include "Game/Game.h"

int main() {
    Game game({800, 800}, "2048");

    game.setFramerateLimit(144);

    while(game.isOpen()){
        game.update();
        game.render();
    }

    return 0;
}
