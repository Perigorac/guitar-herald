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
    window.create(VideoMode(windowWidth,windowHeight),windowtitle);
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
        notepattern[time*10].push_back(temp);
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

int Game::init_decor() {
    if (!columnTexture.loadFromFile(paths[4])) {
        cerr << "Could not load lyre image at " << paths[4] << endl;
        return -1;
    }
    columnSprite.setTexture(columnTexture);
    columnSprite.setScale(CollumnSx,CollumnSy);
    columnSprite.setPosition((int)((windowWidth + 150  - 470*CollumnSx)/2),(int)(windowHeight - 1347*CollumnSx));//On rajoute 150 parce que la fenêtre semble plus grande que windowWidth (plutot 1370 que 1220) et bonne pour windowHeight

    sf::Color spriteColor = columnSprite.getColor();
    spriteColor.a = 150; // Mettre une valeur entre 0 et 255 pour l'opacité
    columnSprite.setColor(spriteColor);
    if (!pressedStringTexture.loadFromFile(paths[6])) {
        std::cerr << "Could not load string pressed image at " << paths[6] << std::endl;
        return -1;
    }

    if (!stringTexture.loadFromFile(paths[5])) {
        std::cerr << "Could not load string image at " << paths[5] << std::endl;
        return -1;
    }
    int xPosition = LINE_BEGIN+80;
    int spacing = LINE_SPACING;
    for (int i = 0; i < 8; ++i) {
        stringsSprites[i].setTexture(stringTexture);
        stringsSprites[i].setPosition(xPosition,0);
        stringsSprites[i].setScale(stringS,stringS*2);      
        xPosition += spacing;
    }

    if (!lyreTexture.loadFromFile(paths[3])) {
        cerr << "Could not load lyre image at " << paths[3] << endl;
        return -1;
    }
    lyreSprite.setTexture(lyreTexture);
    lyreSprite.setScale(LyreSx,LyreSy);
    lyreSprite.setPosition((int)((windowWidth + 150 - 800*LyreSx)/2),(int)(windowHeight - 800*LyreSx));
    return 0;
}

int Game::init_obj_sprites() {
    NormTex.loadFromFile("./assets/BluePuck.png");
    StrumTex.loadFromFile("./assets/Strum.png");
    BonusTex.loadFromFile("./assets/GreenPuck.png");
    LongTex.loadFromFile("./assets/RedPuck.png");
    return 0;
}

// Game processing functions

int Game::launch() {
    score = 0;
    init_window();
    init_music();
    decode_notes();
    init_background();
    init_decor();
    init_obj_sprites();

    framecounter = 0.0f;
    clock.restart(); // The clock and the music player are started just next to each other in order to sync game logic with the music
    lastLoopTime = Time::Zero;
    loop();
    return 0;
}

int Game::event_handler() {
    Event event;
    int line = 0;
    while (window.pollEvent(event)) {
        switch(event.type) {
            case Event::Closed:
                return -1;

            case Event::KeyPressed:
                if(keymap.count(event.key.code) > 0) line_pressed(keymap[event.key.code]);
                break;

            case Event::KeyReleased:
                if(keymap.count(event.key.code) > 0) line_released(keymap[event.key.code]);
                break;

            default:
                break;
        }
    }
    return 0;
}

void Game::line_pressed(int line) {
    int scoremod;
    bool presseffect = true;

    cout << "Pressed line " << line << endl;
    for(auto noteiter = notes.begin(); noteiter != notes.end();) {
        scoremod = (**noteiter).press(line);
        if(scoremod > 0)  {
            cout << "There was an object on this line, worth " << scoremod << " points." << endl;
            score += scoremod;
            noteiter = notes.erase(noteiter);
        } 
        else noteiter++;

        if(scoremod == -1) presseffect = false;
    }
    stringsSprites[line - 1].setTexture(pressedStringTexture);

    if(!presseffect) score-=LINE_NOTHING_SCORE_LOSS;

    return;
}

void Game::line_released(int line) {
    int scoremod = 0;
    cout << "Released line " << line << endl;
    for(auto noteiter = notes.begin(); noteiter != notes.end();) {
        scoremod = (**noteiter).release(line);
        if(scoremod > 0)  {
            cout << "There was an object on this line, worth " << scoremod << " points." << endl;
            score += scoremod;
            noteiter = notes.erase(noteiter);
        } else {
            if(scoremod == -1) score-=LINE_NOTHING_SCORE_LOSS;
            noteiter++;
        }
    }
    stringsSprites[line - 1].setTexture(stringTexture);
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

void Game::displayScore() {
    // Créer un rectangle noir semi-transparent
    RectangleShape background(Vector2f(200, 50));
    background.setFillColor(Color(0, 0, 0, 102)); // Opacité de 40%

    // Positionner le rectangle
    background.setPosition(300, 300);

    // Créer un objet sf::Text pour afficher le score
    Font font;
    if (!font.loadFromFile("./assets/font/HERAKLES.TTF")) {
        std::cerr << "Could not load font file" << std::endl;
        return;
    }

    Text scoreText("Score: " + std::to_string(score), font, 20);
    scoreText.setPosition(300, 300);
    scoreText.setFillColor(Color::White);

    // Dessiner le rectangle et le texte dans la fenêtre
    window.draw(background);
    window.draw(scoreText);
}

void Game::draw_decor() {
    window.draw(columnSprite);
    window.draw(lyreSprite);
    for (int i = 0; i < 8; ++i) {
        window.draw(stringsSprites[i]);
    }
}


int Game::loop() {

    RectangleShape bottomRect;
    bottomRect.setPosition(0,SCREEN_BOTTOM);
    bottomRect.setSize(Vector2f(1360.0,5.0));
    bottomRect.setFillColor(Color::Red);

    while(window.isOpen()) {

        float deltaTime = (clock.getElapsedTime() - lastLoopTime).asMilliseconds();
        lastLoopTime = clock.getElapsedTime();

        // If the music was suspended, play it
        if(music.getStatus() != Music::Playing) {
            framecounter++;
            if(framecounter >= MUSIC_START_DELAY) music.play();
        }

        // Handle events - including control (window closing) and keystrokes
        if(event_handler() == -1) window.close();

        // Check for new notes to insert
        insert_notes();

        // End the game if the note vector is empty
        if(notepattern.empty()) window.close();

        // Clear the window for re-drawing
        window.clear();
        
        // Draw the background first
        window.draw(bgSprite);

        // Draw decor (column, strings...)
        draw_decor();

        // Draw all the notes
        for(auto noteiter = notes.begin(); noteiter != notes.end(); noteiter++) {
            window.draw(**noteiter);
        }

        // Draw additional elements
        window.draw(bottomRect);

        displayScore();

        // Display the window
        window.display();

        // Make all of the notes fall
        for(auto noteiter = notes.begin(); noteiter != notes.end();) {
            if(((**noteiter).fall(SCROLL_SPEED * deltaTime))) {
                score-=(**noteiter).fls();
                noteiter = notes.erase(noteiter);
            }
            else {
                noteiter++;
            }
        }

    }

    return 0;
}
