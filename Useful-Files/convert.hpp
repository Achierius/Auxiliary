#include <algorithm>
#include <iostream>

struct RGB {
    unsigned short r, g, b;
    RGB(unsigned short r1, unsigned short g1, unsigned short b1) {
        r = r1;
        g = g1;
        b = b1;
    }
};
std::ostream& operator<<(std::ostream& os, const RGB& dt);

struct HSV {
    unsigned short h, s, v;
    HSV(unsigned short h1, unsigned short s1, unsigned short v1) {
        h = h1;
        s = s1;
        v = v1;
    }
};
std::ostream& operator<<(std::ostream& os, const HSV& dt);
HSV rgb2Hsv(RGB);
