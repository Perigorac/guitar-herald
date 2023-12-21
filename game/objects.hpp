#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#define FALL_Y 4

using namespace std;
using namespace sf;

class notePattern {

    public:
        void decode(string fpath);

    private:
        vector<int> notevector;
        int BPM;
};

class FallingObject : public sf::Drawable { // Abstract

    public:
        void fall();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        float y;
        Sprite sprite;
};

class StrumLine : public FallingObject {

    
};

class RoundPuck : public FallingObject {

    private:
        int line; // from 1 to 8
};

class NormalPuck : public RoundPuck {
    
    private:
        char letter;
};

class BonusPuck : public RoundPuck {
    
    private:
        int pointvalue;

};

class LongPuck : public RoundPuck {

};