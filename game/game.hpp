#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdio>
#include <map>
#include "objects.hpp"

#define FPS_LIMIT 60
#define windowWidth 1220
#define windowHeight 720

#define SCROLL_SPEED 0.1f // pixel per frame
#define MUSIC_START_DELAY (SCROLL_SPEED * (SCREEN_BOTTOM - (puckS * 128)) * 6) // gives a number of frames to delay music.play()

#define stringS 0.5f
#define LyreSx 1.25f
#define LyreSy 1.25f
#define ColumnSx 0.95f
#define ColumnSy 0.95f

#define LINE_NOTHING_SCORE_LOSS 1

class Game {
    private :

        vector<string> paths; // order of paths : track, notes, background, column

        RenderWindow window;
        string windowtitle;

        Clock clock;
        Time lastLoopTime;
        
        int score;
        map<int,vector<string>> notepattern; // the note pattern for the current song, loaded from the associated text file
        // The format of strings (one string correspoonds to one note) is : "TYPE,LINE,PARAM" - PARAM being an additional parameter :
        // Length for long pucks, value for bonus pucks.
        vector<FallingObject *> notes; // all of the notes currently on screen

        // Background-related
        Texture bgTexture;
        Sprite bgSprite;

        // Decor-related
        Texture lyreTexture;
        Sprite lyreSprite;
        Texture columnTexture;
        Sprite columnSprite;
        Texture stringTexture;
        Texture pressedStringTexture;
        Sprite stringsSprites[8];

        // Music-related
        Music music;
        float framecounter;

    public : 
        Game(string title, vector<string> pathvector);
        int launch();
        int loop();

        int init_window();
        int init_music();
        int decode_notes();
        int init_background();
        int init_decor();
        int init_obj_sprites();

        int event_handler();
        void insert_notes();
        void displayScore();
        void draw_decor();
        void line_pressed(int line);
        void line_released(int line);
};