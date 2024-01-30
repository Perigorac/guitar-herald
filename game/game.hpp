#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdio>
#include <map>
#include "objects.hpp"

#define FPS_LIMIT 60
#define windowWidth 1220
#define windowHeight 720

#define SCROLL_SPEED 0.1f // pixel per frame
#define MUSIC_START_DELAY (SCROLL_SPEED * (SCREEN_BOTTOM - (puckS * 128.0f)) * 6.0f) // gives a number of frames to delay music.play()

#define stringS 0.5f
#define LyreSx 1.25f
#define LyreSy 1.25f
#define ColumnSx 0.95f
#define ColumnSy 0.95f

#define LINE_NOTHING_SCORE_LOSS 1

class Game {

    private :
    
        vector<string> paths; // Order of paths : audio track, notes, background, lyre, column

        RenderWindow window;
        string windowtitle;

        Clock clock;
        Time lastLoopTime;
        
        int score;
        map<int,vector<string>> notepattern; /* The note pattern for the current song, loaded from the associated text file. 
        Basically functions as a queue of notes to insert to the game screen.
        The format of strings (one string correspoonds to one note) is : "TYPE,LINE,PARAM" - PARAM being an additional parameter :
        Length for long pucks, value for bonus pucks. */
        vector<FallingObject *> notes; // All of the notes currently on screen, as objects
        bool user_closed;

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
        Sprite stringsSprites[8]; // Each individual string's sprite

        // Music-related
        Music music;
        float framecounter;

    public : 
        Game(string title, vector<string> pathvector);
        int launch();
        // TEST
        int loop(); 

        // Init functions for game objects

        int init_window();
        // Loads music from given file (a costly operation) but doesn't play it
        int init_music();
        // Loads notes from the given .note file to notepattern
        int decode_notes();
        // Inits the large background sprite
        int init_background();
        // Inits sprites for the lyre, strings, and column
        int init_decor();
        // Loads textures for notes and pucks from files
        int load_obj_textures();

        // Display functions

        // Displays an up-to-date score
        void displayScore();
        // Displays lyre, strings, and column
        void draw_decor();

        // Game processing functions

        // Handles events from the main loop (supports Closed, KeyPressed, and KeyReleased)
        int event_handler();
        // Instanciates note objects from the notepattern, removing them from the queue in the process
        void insert_notes();

        void line_pressed(int line);
        void line_released(int line);
};