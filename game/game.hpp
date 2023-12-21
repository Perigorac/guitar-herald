#include <SFML/Audio.hpp>
#include <iostream>
#include <set>
#include <map>
#include "objects.hpp"

class Game {
    private :

        vector<string> paths; // order of paths : track, notes, background, column

        RenderWindow window;
        string windowtitle;
        Clock clock;

        float scrollSpeed; // pixels par seconde
        int score;
        notePattern NP;
        vector<FallingObject> notes; // all of the notes currently loaded

        // Background-related
        Texture bgTexture;
        Sprite bgSprite;

        // Music-related
        Music music;

    public : 
        Game(string title, vector<string> pathvector);
        int launch();
        int loop();

        int init_window();
        int init_background();
        int init_column();
        int init_music();

        int event_handler();
        void line_pressed(int line);
        void line_released(int line);
};