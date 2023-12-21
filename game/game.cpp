#include "game.hpp"

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

int Game::init_background() {
    if (!bgTexture.loadFromFile(paths[2])) {
        std::cerr << "Could not load background image" << std::endl;
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

int Game::init_music() {
    if (!music.openFromFile(paths[0])) { 
        std::cerr << "Could not load music track" << paths[0] << std::endl;
        return -1;
    }
    music.pause();
    return 0;   
}

// Game processing functions

int Game::launch() {
    score = 0;
    init_window();
    init_background();
    // init_music();
    // music.play();
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

        // First step : clear the window
        window.clear();
        
        // Draw the background first
        window.draw(bgSprite);

        // Display the window
        window.display();
    }

    return 0;
}