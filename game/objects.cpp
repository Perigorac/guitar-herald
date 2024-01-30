#include "objects.hpp"

// TEXTURES

Texture StrumTex;
Texture NormTex;
Texture BonusTex;
Texture LongTex;

Font NpFont;

// FALLING OBJECT

FallingObject& FallingObject::operator+=(float yfall) {
    sprite.move(Vector2f(0.0f, yfall));
    y += yfall;
    return *this;
}

bool FallingObject::fall(float yfall) {
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
    text.setOutlineThickness(1);
    text.setPosition(sprite.getPosition()+Vector2f(15.0f,9.0f));
    wchar_t rndmchar = 0x1D21D + rand() % 0x023; // Generate random Unicode character in range 1D21D ~ 1D241
    text.setString(rndmchar);
}

bool NormalPuck::fall(float yfall) {
    text.move(Vector2f(0.0f, yfall));
    return FallingObject::fall(yfall);
}

void NormalPuck::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    FallingObject::draw(target,states);
    target.draw(text);
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

// LONG PUCK - NOT IMPLEMENTED

LongPuck::LongPuck(int l, int len) : RoundPuck(l) {
    // Create texture for out-of-bounds rendering
    renderTexture.create(BonusTex.getSize().x, BonusTex.getSize().y + len*BonusTex.getSize().y);
    renderTexture.clear(Color::Yellow);

    // Draw sprite on said texture
    spriteTex.setTexture(BonusTex);
    spriteTex.setPosition(0, (BonusTex.getSize().y + (len-1)*BonusTex.getSize().y));

    // Draw trailing rectangle on said texture
    backgroundLine.setSize(Vector2f(20, BonusTex.getSize().y + len*BonusTex.getSize().y));
    backgroundLine.setFillColor(Color(200,0,0, static_cast<Uint8>(250)));
    backgroundLine.setPosition(BonusTex.getSize().x/2 - 10,0);

    renderTexture.draw(backgroundLine);
    renderTexture.draw(spriteTex);

    // display the RenderTexture (behaves like a "sub window")
    renderTexture.display();

    // set the RenderTexture in the sprite in order to benefit from FallingObject::draw()
    float offset = backgroundLine.getSize().y - spriteTex.getLocalBounds().height;
    sprite.setTexture(renderTexture.getTexture());
    sprite.setPosition(Vector2f(LINE_BEGIN + l*LINE_SPACING , -200.0f)); //(len*BonusTex.getSize().y)));
}

int LongPuck::press(int l) {
    if(isInZone() && l == line) {
        pressed = true;
       return 0; 
    }
    return -1;
}

int LongPuck::release(int l) {
    return 0;  
}