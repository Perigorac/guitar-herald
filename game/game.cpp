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
    window.setFramerateLimit(FPS_LIMIT);
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

int Game::decode_notes() {
    FILE * notefile = fopen(paths[1].c_str(),"r");
    if(notefile == NULL) {
        cerr << "Could not load note file at " << paths[1] << endl;
        return -1;
    }

    while(!feof(notefile)) {
        int time, line, param;
        char ntype;
        vector<int> v;
        if(fscanf(notefile,"%d\t%c\t%d\t%d",&time,&ntype,&line,&param) < 2) break;
        // cout << "Time= " << time << ", type=" << ntype << ", line=" << line << ", param=" << param << endl;
        string temp = string(1,ntype) + "," + to_string(line) + "," + to_string(param);
        notepattern[time].push_back(temp);
    }
    
    fclose(notefile);

    // for(auto npiter = notepattern.begin(); npiter != notepattern.end(); npiter++) {
    //     for(auto striter = npiter->second.begin(); striter != npiter->second.end(); striter++) {
    //         cout << *striter << endl;
    //     }
    // }

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

int Game::init_obj_sprites() {
    NormTex.loadFromFile("./assets/BluePuck.png");
    BonusTex.loadFromFile("./assets/GreenPuck.png");
    return 0;
}

// Game processing functions

int Game::launch() {
    score = 0;
    scrollSpeed = 0.1f;
    init_window();
    init_music();
    decode_notes();
    init_background();
    // init_column();
    init_obj_sprites();

    music.play();
    clock.restart(); // The clock and the music player are started just next to each other in order to sync game logic with the music
    lastLoopTime = Time::Zero;
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

void Game::insert_notes() {

    if(notepattern.empty()) return;
    int next_ms = notepattern.begin()->first;

    if(clock.getElapsedTime().asMilliseconds() >= next_ms) {
        while(!notepattern[next_ms].empty()) {
            string next_note = notepattern[next_ms].back();
            cout << "ms = " << next_ms << ", adding " << next_note << endl;
            char t;
            int l,p;
            sscanf(next_note.c_str(),"%c,%d,%d",&t,&l,&p);
            // cout << "t = " << t << ", l = " << l << ", r = " << r << endl;
            
            switch(t) {
                case 'N':
                    notes.push_back(new NormalPuck(l));
                    break;

                case 'L' :
                    notes.push_back(new LongPuck(l,p));
                    break;

                case 'S' :
                    notes.push_back(new StrumLine);
                    break;

                case 'B' :
                    notes.push_back(new BonusPuck(l,p));
                    break;
                    
                default:
                    break;
            }
            notepattern[next_ms].pop_back();
        }
        notepattern.erase(next_ms);
    }
}

int Game::loop() {

    while(window.isOpen()) {

        float deltaTime = (clock.getElapsedTime() - lastLoopTime).asMilliseconds();
        lastLoopTime = clock.getElapsedTime();

        // cout << "Delta = " << deltaTime << endl;

        // Handle events - including control (window closing) and keystrokes
        if(event_handler() == -1) window.close();

        // Check for new notes to insert
        insert_notes();

        // End the game if the note vector is empty
        if(notes.empty()) window.close();

        // Clear the window for re-drawing
        window.clear();
        
        // Draw the background first
        window.draw(bgSprite);

        // Draw the column

        // Draw all the notes
        for(auto noteiter = notes.begin(); noteiter != notes.end(); noteiter++) {
            window.draw(**noteiter);
        }

        // Display the window
        window.display();

        // Make all of the notes fall
        for(auto noteiter = notes.begin(); noteiter != notes.end();) {
            if(((**noteiter).fall(scrollSpeed * deltaTime))) {
                score--;
                cout << "FALLEN !" << endl;
                noteiter = notes.erase(noteiter);
                cout << "ERASED !" << endl;
            }
            else {
                noteiter++;
            }
        }

    }

    return 0;
}