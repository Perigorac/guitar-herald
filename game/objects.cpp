#include "objects.hpp"

// TEXTURES

Texture StrumTex;
Texture NormTex;
Texture BonusTex;
Texture LongTex;

Font NpFont;

// FALLING OBJECT
FallingObject& FallingObject::operator+=(float yfall) {
    sprite.move(sf::Vector2f(0.0f, yfall));
    y += yfall;
    return *this;
}

bool FallingObject::fall(float yfall) {
    // this method implements basic physics of any note / falling object - fall by a certain amount
    // Return true whenever the FallingObject falls beyond the bottom of the screen
    *this += yfall;
    return (y > SCREEN_BOTTOM);
}

// STRUM LINE

StrumLine::StrumLine() {
    sprite.setTexture(StrumTex);
    sprite.setPosition(Vector2f(LINE_BEGIN + 50 ,0.0f));
    sprite.setScale(strumS,strumS);
    linePressed.resize(8);
    for(auto lPiter = linePressed.begin(); lPiter != linePressed.end(); lPiter++) *lPiter = false;
}

int StrumLine::press(int line) {
    if(isInZone()) {
        linePressed[line] = true;
        int nbpressed = 0;
        for(auto lPiter = linePressed.begin(); lPiter != linePressed.end(); lPiter++) if(*lPiter) nbpressed++;
        if(nbpressed > 5) { // Everything is 'true', all lines have been pressed
            return STRUM_VALUE;
        }
        else {
            return 0;
        }
    }
    else {
        return -1;
    }
}

// ROUND PUCK

RoundPuck::RoundPuck(int l) {
    line = l;
    sprite.setPosition(Vector2f(LINE_BEGIN + l*LINE_SPACING,0.0f));
    sprite.setScale(puckS,puckS);
    pressed = false;
}

int RoundPuck::press(int l) {
    if(isInZone()) {
       if(l == line) pressed = true;
       return 0; 
    }
    return -1;
}

int RoundPuck::release(int l) {
    if((l == line) && pressed) {
        return NORMAL_VALUE;
    }
    else {
        return 0;
    }
}

// NORMAL PUCK

NormalPuck::NormalPuck(int l) : RoundPuck(l) {
    sprite.setTexture(NormTex);
    text.setFont(NpFont);
    text.setString("AAAAA");
}

void NormalPuck::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite);
}

// BONUS PUCK

int BonusPuck::release(int l) {
    if((l == line) && pressed) {
        return pointvalue;
    }
    else {
        return 0;
    }
}

// LONG PUCK

LongPuck::LongPuck(int l, int len) : RoundPuck(l) {
    // Créer la texture pour le rendu hors écran
    renderTexture.create(BonusTex.getSize().x, BonusTex.getSize().y + len*BonusTex.getSize().y);
    renderTexture.clear(Color::Transparent);

    // Dessiner le sprite sur la texture
    Sprite spriteTex;
    spriteTex.setTexture(BonusTex);
    spriteTex.setPosition(0, (BonusTex.getSize().y + (len-1)*BonusTex.getSize().y));

    // Dessiner le rectangle sur la texture
    backgroundLine.setSize(Vector2f(20, BonusTex.getSize().y + len*BonusTex.getSize().y));
    backgroundLine.setFillColor(Color(200,0,0, static_cast<Uint8>(250)));
    backgroundLine.setPosition(BonusTex.getSize().x/2 - 10,0);//sprite.getPosition());


    renderTexture.draw(backgroundLine);
    renderTexture.draw(spriteTex);

    // Finir le rendu hors écran
    renderTexture.display();

    sprite.setTexture(renderTexture.getTexture());
    sprite.setPosition(Vector2f(LINE_BEGIN + l*LINE_SPACING ,0)); //(len*BonusTex.getSize().y)));
    // sprite.setScale(0.55f,0.55f);
}