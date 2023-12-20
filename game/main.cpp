#include "game.hpp"
#include <iostream>

int main() {

    vector<string> pathvector = {"","","./assets/DelphiTheatre.jpg",""};
    Game testgame("Testgame",pathvector);
    testgame.launch();

    return 0;
}
