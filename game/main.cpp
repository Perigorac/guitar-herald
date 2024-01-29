#include "game.hpp"
#include <iostream>

RenderWindow window;

Font GUITARFont;
Font HERALDFont;
Font ScoreFont;

Text GUITARText("GUITAR",GUITARFont,140);
Text HERALDText("HERALD",HERALDFont,100);
Text ScoreText("Your Score : 0 ",ScoreFont,60);

Texture bgTexture;
Sprite bgSprite;

void init_elements(int score) {

    window.create(VideoMode(windowWidth,windowHeight),"CONGRATULATIONS !!");
    window.setPosition(Vector2i(200,100));
    window.requestFocus();
    window.setFramerateLimit(FPS_LIMIT);
    
    GUITARFont.loadFromFile("./assets/font/metal_lord.otf");
    HERALDFont.loadFromFile("./assets/font/HERAKLES.TTF");
    ScoreFont.loadFromFile("./assets/font/Quivira.otf");
    
    GUITARText.setPosition(60,10);
    GUITARText.setFillColor(Color::White);

    HERALDText.setPosition(130,155);
    HERALDText.setFillColor(Color::White);

    ScoreText.setPosition(130,350);
    ScoreText.setFillColor(Color::White);
    ScoreText.setString("Your Score : " + to_string(score));

    bgTexture.loadFromFile("./assets/bg/Pandemonium.jpg");
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(static_cast<float>(window.getSize().x) / bgTexture.getSize().x,
                    static_cast<float>(window.getSize().y) / bgTexture.getSize().y);
}

int main() {

    int score;
    vector<string> pathvector = {"./audio/Seikilos_Epitaph_Full.ogg","./SeikilosNote.txt","./assets/bg/DelphiTheatre.jpg","./assets/Lyre.png","./assets/SekilosUnstroked.png", "./assets/NylonString.png", "./assets/NylonStringPressed.png"};
    Game Seikilos("Seikilos",pathvector);
    score = Seikilos.launch();
    // score = 50;

    if(score == -1) {
        cout << "Error in game" << endl;
        return -1;
    }
    else {
        cout << "Game over" << endl;

        init_elements(score);

        while(window.isOpen()) {

            Event event;
            while(window.pollEvent(event)) {
                if(event.type == Event::Closed) window.close();
            }

            window.clear();

            window.draw(bgSprite);
            window.draw(GUITARText);
            window.draw(HERALDText);
            window.draw(ScoreText);

            window.display();
        }

    }
    return 0;
}
