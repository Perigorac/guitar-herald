#include "game.hpp"
#include <iostream>

int main() {

    vector<string> pathvector = {"./audio/Seikilos_Epitaph_Full.ogg","./testnote.txt","./assets/DelphiTheatre.jpg",""};
    Game Seikilos("Seikilos",pathvector);
    Seikilos.launch();

    return 0;
}
