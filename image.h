// CIS 330
// Project 3E
//
// Samuel Svindland
// 951472606
// ssvindla@cs.uoregon.edu
//
#include "filter.h"

#ifndef IMAGE_H
#define IMAGE_H

class Source;

struct Pixel {
    unsigned char r, g, b;
};

class Image {
public:
    Image();
    virtual ~Image();

    int GetWidth();
    int GetHeight();
    Pixel *GetBuffer();

    void SetWidth(int);
    void SetHeight(int);
    void SetBuffer(Pixel *);

    Pixel GetSinglePixel(int, int);
    void SetSinglePixel(int, int, Pixel);

    virtual void Update();
    void SetSource(Source *);
private:
    int width, height;
    Pixel *pixel;
    Source *source;
};

#endif