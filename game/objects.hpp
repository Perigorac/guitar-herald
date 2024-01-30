#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

#define SCREEN_BOTTOM 642.0f
#define LINE_BEGIN 410
#define LINE_SPACING 55

//Texture scale factors
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

class FallingObject : virtual public Drawable { // Abstract

    public:
        FallingObject() {y = 0.0f;}
        /* this method implements basic physics of any note / falling object - fall by a certain amount
        Returns true whenever the FallingObject falls beyond the bottom of the screen
        It is made virtual so it can be overloaded in NormalPuck */
        virtual bool fall(float yfall);
        /*Virtual class inherited from Drawable that eases drawing of complex object*/
        void draw(RenderTarget &target, RenderStates states) const {target.draw(sprite);}
        virtual ~FallingObject() {};
        /*Response to a press on line l - even StrumLines need this info*/
        virtual int press(int l) {return 0;}
        /*Response to a release on line l*/
        virtual int release(int l) {return 0;}
        // Getter for each note's FLS
        virtual int fls() {return 0;}

    protected:
        float y;
        Sprite sprite;
        bool operator>=(float value) const {return y + static_cast<float>(sprite.getLocalBounds().height) >= value;}
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

class RoundPuck : virtual public FallingObject {

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
        bool fall(float yfall);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        int fls() {return NORMAL_FLS;}
    private:
        Text text;
};

class BonusPuck : public RoundPuck {
    
    public:
        BonusPuck(int l, int value) : RoundPuck(l) {sprite.setTexture(BonusTex); pointvalue = value;}
        int release(int l);
        int fls() {return 0;}
    private:
        int pointvalue;

};

// NOT IMPLEMENTED
class LongPuck : public RoundPuck { 
    public:
        LongPuck(int l, int len);
        int fls() {return LONG_FLS;}
        int press(int l);
        int release(int l); // Not implemented due to obtuse key-holding mechanics SFML
    private:
        int length;
        int counter;
        RectangleShape backgroundLine; // Draw a trailing rectangle on the LongPuck
        RenderTexture renderTexture; // Texture that includes spriteTex and backgroundLine, in order to be drawn outside of the screen
        Sprite spriteTex;
};