#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

#define SCREEN_BOTTOM 622.0f
#define LINE_BEGIN 410
#define LINE_SPACING 55

//Texture sizes
#define puckS 0.42f
#define strumS 0.55f

// Point values
#define STRUM_VALUE 10
#define NORMAL_VALUE 5
#define LONG_VALUE 5

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

extern Font NpFont;

class FallingObject : public Drawable { // Abstract

    public:
        FallingObject() {y = 0.0f;}
        bool fall(float yfall);
        void draw(RenderTarget &target, RenderStates states) const {target.draw(sprite);}
        virtual ~FallingObject() {};
        virtual int press(int l) {return 0;}
        virtual int release(int l) {return 0;}
        virtual int fls() {return 0;}

    protected:
        float y;
        Sprite sprite;
        float operator>=(float value) const {return y + static_cast<float>(sprite.getLocalBounds().height) >= value;}
        FallingObject& operator+=(float yfall);
        bool isInZone() {return *this >= SCREEN_BOTTOM;}
};

class StrumLine : public FallingObject {
    
    public:
        StrumLine();
        int press(int l);
        int fls() {return STRUM_FLS;}
    private:
        vector<bool> linePressed;
    
};

class RoundPuck : public FallingObject {

    public:
        RoundPuck(int l);
        int press(int l);
        int release(int l);
    protected:
        bool pressed;
        int line; // from 1 to 8
};

class NormalPuck : public RoundPuck {

    public:
        NormalPuck(int l);
        int fls() {return NORMAL_FLS;}
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    private:
        Text text;
};

class BonusPuck : public RoundPuck {
    
    public:
        BonusPuck(int l, int value) : RoundPuck(l) {sprite.setTexture(BonusTex);}
        int release(int l);
        int fls() {return 0;}
    private:
        int pointvalue;

};

class LongPuck : public RoundPuck {
    public:
        LongPuck(int l, int len);
        int fls() {return LONG_FLS;}

    private:
        int length;
        RectangleShape backgroundLine;
        RenderTexture renderTexture;
};