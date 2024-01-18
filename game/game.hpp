#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdio>
#include <map>
#include "objects.hpp"

#define FPS_LIMIT 60

class Game {
    private :

        vector<string> paths; // order of paths : track, notes, background, column

        RenderWindow window;
        string windowtitle;

        Clock clock;
        Time lastLoopTime;
        
        float scrollSpeed; // pixels par seconde
        int score;
        map<int,vector<string>> notepattern; // the note pattern for the current song, loaded from the associated text file
        // The format of strings (one string correspoonds to one note) is : "TYPE,LINE,PARAM" - PARAM being an additional parameter :
        // Length for long pucks, value for bonus pucks.
        vector<FallingObject *> notes; // all of the notes currently on screen

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
        int init_music();
        int decode_notes();
        int init_background();
        int init_column();
        int init_obj_sprites();

        int event_handler();
        void insert_notes();
        void line_pressed(int line);
        void line_released(int line);
};