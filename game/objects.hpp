#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

#define SCREEN_BOTTOM 500.0f
#define ZONE_SIZE 50.0f
#define SCREEN_ZONE (SCREEN_BOTTOM - ZONE_SIZE)
#define LINE_BEGIN 100
#define LINE_SPACING 150

using namespace std;
using namespace sf;

extern Texture StrumTex;
extern Texture NormTex;
extern Texture BonusTex;
extern Texture LongTex;

class FallingObject : public Drawable { // Abstract

    public:
        FallingObject() {y = 0.0f;}
        bool fall(float yfall);
        virtual void draw(RenderTarget &target, RenderStates states) const {}
        virtual int computeScore() const {return 5;}
        virtual ~FallingObject() {};
        virtual int press(int l) {return 0;}
        virtual int release(int l) {return 0;}

    protected:
        bool isInZone() {return y + (float)((sprite.getLocalBounds()).height) >= SCREEN_ZONE;}
        float y;
        Sprite sprite;
};

class StrumLine : public FallingObject {
    
    public:
        StrumLine();
        void draw(RenderTarget &target, RenderStates states) const {};
        int press(int l);
    private:
        vector<bool> linePressed;
    
};

class RoundPuck : public FallingObject {

    public:
        RoundPuck(int l);
        void draw(RenderTarget &target, RenderStates states) const {};
        int press(int l);
        int release(int l);
    protected:
        bool pressed;
        int line; // from 1 to 8
};

class NormalPuck : public RoundPuck {

    public:
        NormalPuck(int l) : RoundPuck(l) {sprite.setTexture(NormTex);}
        void draw(RenderTarget &target, RenderStates states) const;
    private:
        char letter;
};

class BonusPuck : public RoundPuck {
    
    public:
        BonusPuck(int l, int value) : RoundPuck(l) {sprite.setTexture(BonusTex);}
        void draw(RenderTarget &target, RenderStates states) const;
    private:
        int pointvalue;

};

class LongPuck : public RoundPuck {
    public:
        LongPuck(int l, int len) : RoundPuck(l) {sprite.setTexture(LongTex);}
        void draw(RenderTarget &target, RenderStates states) const {};

    private:
        int length;
};