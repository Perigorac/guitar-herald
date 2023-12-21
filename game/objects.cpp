#include "objects.hpp"

int FallingObject::fall(float yfall) {
    if(y + yfall > SCREEN_BOTTOM) {
        return -1;
    }
    else {
        return 0;
    }
}