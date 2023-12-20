#include <game.hpp>

// Constructors

Game::Game(string title, vector<string> pathvector) {
    paths = pathvector;
    windowtitle = title;
}

int Game::init_window() {
    window.create(sf::VideoMode(1220,720),windowtitle);
    window.requestFocus();
}

int Game::init_background() {
    if (!bgTexture.loadFromFile(paths[2])) {
        std::cerr << "Erreur lors du chargement de l'image de fond 1" << std::endl;
        return 1;
    }
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(static_cast<float>(window.getSize().x) / bgTexture.getSize().x,
                      static_cast<float>(window.getSize().y) / bgTexture.getSize().y);
}

int Game::init_column() {
    return 0;
}

int Game::init_music() {
    if (!music.openFromFile(paths[0])) { 
        std::cerr << "Could not load music track " << paths[0] << std::endl;
        return -1;
    }
    music.pause();
    return 0;   
}

int Game::launch() {
    init_window();
    init_music();
    init_background();
    music.play();
    loop();
}

int Game::loop() {

    while(window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // First step : clear the window
        window.clear();
        
        // Draw the background first
        window.draw(bgSprite);

        // Display the window
        window.display();
    }

    return 0;
}