#include "game.hpp"
#include <iostream>

int main() {

    vector<string> pathvector = {"./audio/Seikilos_Epitaph_Full.ogg","./SeikilosNote.txt","./assets/DelphiTheatre.jpg","./assets/Lyre.png","./assets/SekilosUnstroked.png", "./assets/NylonString.png", "./assets/NylonStringPressed.png"};
    Game Seikilos("Seikilos",pathvector);
    Seikilos.launch();

    return 0;
}
