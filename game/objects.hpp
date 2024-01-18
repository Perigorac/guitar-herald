#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

#define SCREEN_BOTTOM 300.0f
#define LINE_BEGIN 100
#define LINE_SPACING 150

using namespace std;
using namespace sf;

extern Texture StrumTex;
extern Texture NormTex;
extern Texture BonusTex;
extern Texture LongTex;

class FallingObject : public sf::Drawable { // Abstract

    public:
        FallingObject() {y = 0.0f;}
        bool fall(float yfall);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {};
        virtual int computeScore() const {return 0;};
        virtual ~FallingObject() {};

    protected:
        float y;
        Sprite sprite;
};

class StrumLine : public FallingObject {
    public:
        StrumLine() {sprite.setTexture(StrumTex);}
        void draw(sf::RenderTarget &target, sf::RenderStates states) const {};
    
};

class RoundPuck : public FallingObject {

    public:
        RoundPuck(int l);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const {};
    protected:
        int line; // from 1 to 8
};

class NormalPuck : public RoundPuck {
    public:
        NormalPuck(int l) : RoundPuck(l) {sprite.setTexture(NormTex);}
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    private:
        char letter;
};

class BonusPuck : public RoundPuck {
    
    public:
        BonusPuck(int l, int value) : RoundPuck(l) {sprite.setTexture(BonusTex);}
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    private:
        int pointvalue;

};

class LongPuck : public RoundPuck {
    public:
        LongPuck(int l, int len) : RoundPuck(l) {sprite.setTexture(LongTex);}
        void draw(sf::RenderTarget &target, sf::RenderStates states) const {};

    private:
        int length;
};