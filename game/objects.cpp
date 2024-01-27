#include "objects.hpp"

// TEXTURES

Texture StrumTex;
Texture NormTex;
Texture BonusTex;
Texture LongTex;

// FALLING OBJECT

bool FallingObject::fall(float yfall) {
    // this method implements basic physics of any note / falling object - fall by a certain amount
    // Return true whenever the FallingObject falls beyond the bottom of the screen
    sprite.move(Vector2f(0.0f,yfall));
    y+=yfall;
    // cout << y << endl;
    return (y > SCREEN_BOTTOM);
}

// STRUM LINE

StrumLine::StrumLine() {
    sprite.setTexture(StrumTex);
    linePressed.resize(8);
    for(auto lPiter = linePressed.begin(); lPiter != linePressed.end(); lPiter++) *lPiter = false;
}

int StrumLine::press(int line) {
    if(isInZone()) {
        linePressed[line] = true;
        bool gBool = true;
        for(auto lPiter = linePressed.begin(); lPiter != linePressed.end(); lPiter++) gBool &= *lPiter;
        if(gBool) { // Everything is 'true', all lines have been pressed
            return computeScore();
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
        return computeScore();
    }
    else {
        return 0;
    }
}

// NORMAL PUCK

void NormalPuck::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite);
}

// BONUS PUCK

void BonusPuck::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite);
}