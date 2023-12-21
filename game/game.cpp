#include "game.hpp"

map<int,vector<int>> notemap = {};

map<Keyboard::Key,int> keymap = {{Keyboard::Q,1},
                                 {Keyboard::S,2},
                                 {Keyboard::D,3},
                                 {Keyboard::F,4},
                                 {Keyboard::J,5},
                                 {Keyboard::K,6},
                                 {Keyboard::L,7},
                                 {Keyboard::M,8},
                                 };

// Constructor

Game::Game(string title, vector<string> pathvector) {
    paths = pathvector;
    windowtitle = title;
}

// Init functions

int Game::init_window() {
    window.create(VideoMode(1220,720),windowtitle);
    window.requestFocus();
    window.setFramerateLimit(60);
    return 0;
}

int Game::init_music() {
    if (!music.openFromFile(paths[0])) { 
        cerr << "Could not load music track at " << paths[0] << endl;
        return -1;
    }
    music.pause();
    return 0;   
}

int Game::init_notes() {
    FILE * notefile = fopen(paths[1].c_str(),"r");
    if(notefile == NULL) {
        cerr << "Could not load note file at " << paths[1] << endl;
        return -1;
    }

    while(!feof(notefile)) {
        int time, line, length;
        char ntype;
        vector<int> v;
        if(fscanf(notefile,"%d\t%c\t%d\t%d",&time,&ntype,&line,&length) < 2) break;
        cout << "Time= " << time << ", type=" << ntype << ", line=" << line << ", length=" << length << endl;
    }
    
    fclose(notefile);
    return 0;
}

int Game::init_background() {
    if (!bgTexture.loadFromFile(paths[2])) {
        cerr << "Could not load background image at " << paths[2] << endl;
        return -1;
    }
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(static_cast<float>(window.getSize().x) / bgTexture.getSize().x,
                      static_cast<float>(window.getSize().y) / bgTexture.getSize().y);
    return 0;
}

int Game::init_column() {
    return 0;
}

// Game processing functions

int Game::launch() {
    score = 0;
    init_window();
    init_music();
    init_notes();
    init_background();
    // init_column();

    music.play();
    loop();
    return 0;
}

int Game::event_handler() {
    Event event;
    while (window.pollEvent(event)) {
        switch(event.type) {
            case Event::Closed:
                return -1;

            case Event::KeyPressed:
                if(keymap.count(event.key.code) > 0) line_pressed(keymap[event.key.code]);
                break;

            // case Event::KeyReleased:
            //     if(keymap.count(event.key.code) > 0) line_released(keymap[event.key.code]);
            //     break;

            default:
                break;
        }
    }
    return 0;
}

void Game::line_pressed(int line) {
    cout << "Pressed line " << line << endl;
    score--;
    return;
}

int Game::loop() {

    while(window.isOpen()) {

        float deltaTime = clock.restart().asSeconds();

        if(event_handler() == -1) window.close();

        // Make all of the objects fall
        for(auto noteiter = notes.begin(); noteiter != notes.end(); noteiter++) {
            score -= (*noteiter).fall(scrollSpeed * deltaTime);
        }

        // First step : clear the window
        window.clear();
        
        // Draw the background first
        window.draw(bgSprite);

        // Draw the column

        // Draw all the notes
        for(auto noteiter = notes.begin(); noteiter != notes.end(); noteiter++) {
            window.draw(*noteiter);
        }

        // Display the window
        window.display();
    }

    return 0;
}