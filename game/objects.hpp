#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

#define SCREEN_BOTTOM 632.0f
#define ZONE_SIZE 50.0f
#define SCREEN_ZONE (SCREEN_BOTTOM - ZONE_SIZE)
#define LINE_BEGIN 410
#define LINE_SPACING 55

//Texture sizes
#define puckS 0.42f
#define stringS 0.5f
#define LyreSx 1.25f
#define LyreSy 1.25f
#define CollumnSx 0.95f
#define CollumnSy 0.95f

// FLS stands for "Fall Score Loss"
#define NORMAL_FLS 5
#define STRUM_FLS 5
#define LONG_FLS 5

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
        virtual int fls() {return 0;}

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
        int fls() {return STRUM_FLS;}
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
        int fls() {return NORMAL_FLS;}
    private:
        char letter;
};

class BonusPuck : public RoundPuck {
    
    public:
        BonusPuck(int l, int value) : RoundPuck(l) {sprite.setTexture(BonusTex);}
        void draw(RenderTarget &target, RenderStates states) const;
        int fls() {return 0;}
    private:
        int pointvalue;

};

class LongPuck : public RoundPuck {
    public:
        LongPuck(int l, int len) : RoundPuck(l) {sprite.setTexture(LongTex);}
        void draw(RenderTarget &target, RenderStates states) const {};
        int fls() {return LONG_FLS;}

    private:
        int length;
};