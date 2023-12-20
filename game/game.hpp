#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <iostream>
#include <string>
#include "objects.hpp"

using namespace std;

class Game {
    private :

        sf::RenderWindow window;
        string windowtitle;
        sf::Clock clock;

        float scrollSpeed; // pixels par seconde
        int score;
        notePattern NP;
        vector<string> paths; // order of paths : track, notes, background, column

        // Background-related
        sf::Texture bgTexture;
        sf::Sprite bgSprite;

        // Music-related
        sf::Music music;

    public : 
        Game(string title, vector<string> pathvector);
        int launch();
        int loop();

        int init_window();
        int init_background();
        int init_column();
        int init_music();
};