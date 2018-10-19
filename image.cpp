// CIS 330
// Project 3E
//
// Samuel Svindland
// 951472606
// ssvindla@cs.uoregon.edu
//
#include <iostream>
#include "image.h"

Image::Image() {
    this->width = 0;
    this->height = 0;
    this->pixel = nullptr;
}

Image::~Image() {

}

int Image::GetWidth() {
    return this->width;
}

int Image::GetHeight() {
    return this->height;
}

Pixel *Image::GetBuffer() {
    return this->pixel;
}

void Image::SetWidth(int width) {
    this->width = width;
}

void Image::SetHeight(int height) {
    this->height = height;
}

void Image::SetBuffer(Pixel *pixel) {
    this->pixel = pixel;
}

Pixel Image::GetSinglePixel(int i, int j) {
    return pixel[j*width+i];
}

void Image::SetSinglePixel(int i, int j, Pixel new_pixel) {
    pixel[j*width+i] = new_pixel;
}

void Image::Update() {
    source->Update();
}

void Image::SetSource(Source *source) {
    if (source != nullptr) {
        this->source = source;
    }
}