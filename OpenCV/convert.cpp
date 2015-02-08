#include "convert.hpp"
std::ostream& operator<<(std::ostream& os, const HSV& hsv)
{
    os << hsv.h << ',' << hsv.s << ',' << hsv.v;
    return os;
}

std::ostream& operator<<(std::ostream& os, const RGB& rgb)
{
    os << rgb.r << ',' << rgb.g << ',' << rgb.b;
    return os;
}

HSV rgb2Hsv(RGB rgb) {
    double r = rgb.r / 255.;
    double g = rgb.g / 255.;
    double b = rgb.b / 255.;

    double max = std::max(std::max(r, g), b);
    double min = std::min(std::min(r, g), b);

    double h, s, v = max;
    double d = max - min;
    s = max == 0 ? 0 : d / max;

    if(max == min) {
        h = 0; // no color
    } else {
        if(max == r) h = (g - b) / d + (g < b ? 6 : 0);
        else if(max == g) h = (b - r) / d + 2;
        else if(max == b) h = (r - g) / d + 4;
    }
    h /= 6;
    return HSV(h * 255, s * 255, v * 255);
}