#include "utils.hpp"
#include <random>


CRGB getRandomColor()
{
    static const byte length = 8;
    static const CRGB colors[length] = {
        CRGB::Aqua,
        CRGB::Orange,
        CRGB::Chartreuse,
        CRGB::Purple,
        CRGB::MistyRose,
        CRGB::Yellow,
        CRGB::GreenYellow,
        CRGB::Fuchsia,
    };
    
    return colors[rand() % length];
}