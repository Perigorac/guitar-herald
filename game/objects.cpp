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
    cout << y << endl;
    return (y > SCREEN_BOTTOM);
}

// STRUM LINE

// ROUND PUCK

RoundPuck::RoundPuck(int l) {
    line = l;
    sprite.setPosition(Vector2f(LINE_BEGIN + l*LINE_SPACING,0.0f));
}

// NORMAL PUCK

void NormalPuck::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite);
}

// BONUS PUCK

void BonusPuck::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite);
}