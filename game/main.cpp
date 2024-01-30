#include "game.hpp"
#include <iostream>

#define BLINK_HPERIOD_MS 500

RenderWindow window;
Clock bclock;

Font GUITARFont;
Font HERALDFont;
Font ScoreFont;

Text GUITARText("GUITAR",GUITARFont,140);
Text HERALDText("HERALD",HERALDFont,100);
Text ScoreText("Your Score : 0 ",ScoreFont,60);
Text NewRecordText(" NEW \nRECORD",HERALDFont,80);

Texture bgTexture;
Sprite bgSprite;

int best_score;
string holder;

int read_best_score() {
    
    FILE * scorefile = fopen("./best_score.txt","r");
    if(scorefile == NULL) {
        return -1;
    }

    int bs;
    char holderbuffer[256];
    fscanf(scorefile,"%d %s",&bs,holderbuffer);
    fclose(scorefile);

    holder = string(holderbuffer);
    return bs;
}

void write_best_score(int score) {

    string newholder;
    cout << "Enter your name (no spaces nor slashes): " << endl;
    cin >> newholder;
    cout << "Congratulations " << newholder << " !! You are the champion !!" << endl;

    string newstring = to_string(score) +" "+ newholder;
    const char * newbuffer = newstring.c_str();

    FILE * scorefile = fopen("./best_score.txt","w");
    if(scorefile == NULL) {
        return;
    }

    fputs(newbuffer,scorefile);
    fclose(scorefile);
}

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

    ScoreText.setPosition(80,350);
    ScoreText.setFillColor(Color::White);

    best_score = read_best_score();

    if(best_score < 0) {
        cout << "Could not load or read score file" << endl;
        ScoreText.setString("Your Score : " + to_string(score));
    }
    else {
        ScoreText.setString("Your Score : " + to_string(score) + "\n" + "Best Score : " + to_string(best_score) + \
        "\n" + "Held by : " + holder);
        NewRecordText.setPosition(700,80);
        NewRecordText.setFillColor(Color::White);
    }

    bgTexture.loadFromFile("./assets/bg/Pandemonium.jpg");
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(static_cast<float>(window.getSize().x) / bgTexture.getSize().x,
                    static_cast<float>(window.getSize().y) / bgTexture.getSize().y);
}

void blink_record() {
    int elapsed_ms = bclock.getElapsedTime().asMilliseconds();
    if(elapsed_ms > BLINK_HPERIOD_MS) {
        window.draw(NewRecordText);
        if(elapsed_ms > 2 * BLINK_HPERIOD_MS) bclock.restart();
    }
}

int main() {

    int score;
    vector<string> pathvector = {"./audio/Seikilos_Epitaph_Full.ogg","./Seikilos.note","./assets/bg/DelphiTheatre.jpg","./assets/Lyre.png","./assets/SekilosUnstroked.png"};
    Game Seikilos("Seikilos",pathvector);
    score = Seikilos.launch();

    cout << "Game over" << endl;

    if(score == -1) {
        window.close();
        return -1;
    }
    else {
        cout << "You did it !" << endl;

        init_elements(score);
        bclock.restart();

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
            if(score > best_score) blink_record();

            window.display();
        }

        if(score > best_score) {
            write_best_score(score);
        }
    }

    return 0;
}
