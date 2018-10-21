// CIS 330
// Project 3D
//
// Samuel Svindland
// 951472606
// ssvindla@cs.uoregon.edu
//
#include <iostream>

#include "sink.h"

Sink::Sink() {
    this->image1 = nullptr;
    this->image2 = nullptr;
}

void Sink::SetInput(Image *image1) {
    this->image1 = image1;
}

void Sink::SetInput2(Image *image2) {
    this->image2 = image2;
}