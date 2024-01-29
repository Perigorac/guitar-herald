#include "game.hpp"
#include <iostream>

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
        RenderWindow window;
        window.create(VideoMode(windowWidth,windowHeight),"CONGRATULATIONS !!");
        window.setPosition(Vector2i(200,100));
        window.requestFocus();
        window.setFramerateLimit(FPS_LIMIT);
        
        Font GUITARFont;
        Font HERALDFont;
        Font ScoreFont;
        GUITARFont.loadFromFile("./assets/font/metal_lord.otf");
        HERALDFont.loadFromFile("./assets/font/HERAKLES.TTF");
        ScoreFont.loadFromFile("./assets/font/Quivira.otf");

        Text GUITARText("GUITAR",GUITARFont,140);
        GUITARText.setPosition(60,10);
        GUITARText.setFillColor(Color::White);

        Text HERALDText("HERALD",HERALDFont,100);
        HERALDText.setPosition(130,155);
        HERALDText.setFillColor(Color::White);

        Text ScoreText(("Your Score : " + to_string(score)),ScoreFont,60);
        ScoreText.setPosition(130,350);
        ScoreText.setFillColor(Color::White);

        Texture bgTexture;
        Sprite bgSprite;
        !bgTexture.loadFromFile("./assets/bg/Pandemonium.jpg");
        bgSprite.setTexture(bgTexture);
        bgSprite.setScale(static_cast<float>(window.getSize().x) / bgTexture.getSize().x,
                        static_cast<float>(window.getSize().y) / bgTexture.getSize().y);

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
