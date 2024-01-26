#include "game.hpp"
#include <iostream>

int main() {

    vector<string> pathvector = {"./audio/Seikilos_Epitaph_Full.ogg","./SeikilosNote.txt","./assets/DelphiTheatre.jpg",""};
    Game Seikilos("Seikilos",pathvector);
    Seikilos.launch();

    return 0;
}
