// CIS 330
// Project 3D
//
// Samuel Svindland
// 951472606
// ssvindla@cs.uoregon.edu
//
#include <stdio.h>

#include "source.h"

Source::Source() {
    image.SetSource(this);
}

Image *Source::GetOutput() {
    return &this->image;
}
