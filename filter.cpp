// CIS 330
// Project 3D
//
// Samuel Svindland
// 951472606
// ssvindla@cs.uoregon.edu
//
#include <iostream>

#include "filter.h"

void Filter::Update() {
    if(image1 != nullptr) {
        char msg[128];
        sprintf(msg, "%s: about to update image1", FilterName());
        Logger::LogEvent(msg);
        image1->Update();
        sprintf(msg, "%s: done updating image1", FilterName());
        Logger::LogEvent(msg);
    }
    if(image2 != nullptr) {
        char msg[128];
        sprintf(msg, "%s: about to update image2", FilterName());
        Logger::LogEvent(msg);
        image1->Update();
        sprintf(msg, "%s: done updating image2", FilterName());
        Logger::LogEvent(msg);
    }
    char msg[128];
    sprintf(msg, "%s: about to execute", FilterName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", FilterName());
    Logger::LogEvent(msg);
}


void Shrinker::Execute() {
    if (image1 == nullptr) {
        char msg[1024];
        sprintf(msg, "%s: no image1", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else {
        int width = image1->GetWidth() / 2;
        int height = image1->GetHeight() / 2;

        Pixel *pixel = new Pixel[width*height];

        image.SetWidth(width);
        image.SetHeight(height);
        image.SetBuffer(pixel);

        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; j++) {
                Pixel new_pixel = image1->GetSinglePixel(2*i, 2*j);
                image.SetSinglePixel(i, j, new_pixel);
            }
        }
    }
}

void LRCombine::Execute() {
    if (image1 == nullptr) {
        char msg[1024];
        sprintf(msg, "%s: no image1", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else if(image2 == nullptr) {
        char msg[1024];
        sprintf(msg, "%s: no image2", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else {
        int width = image1->GetWidth() + image2->GetWidth();
        int height = image1->GetHeight();
        int temp = image1->GetWidth();

        if (image1->GetHeight() != image2->GetHeight()) {
            char msg[1024];
            sprintf(msg, "%s: height must match: %d, %d", SinkName(), image1->GetHeight(), image2->GetHeight());
            DataFlowException e(SinkName(), msg);
            throw e;
        }
        else {
            Pixel *pixel = new Pixel[width*height];

            image.SetWidth(width);
            image.SetHeight(height);
            image.SetBuffer(pixel);

            for(int i = 0; i < temp; i++) {
                for(int j = 0; j < height; j++) {
                    Pixel leftPixel = image1->GetSinglePixel(i, j);
                    Pixel rightPixel = image2->GetSinglePixel(i, j);
                    image.SetSinglePixel(i, j, leftPixel);
                    image.SetSinglePixel(i+temp, j, rightPixel);
                }
            }
        }
    }
}

void TBCombine::Execute() {
    if (image1 == nullptr) {
        char msg[1024];
        sprintf(msg, "%s: no image1", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else if(image2 == nullptr) {
        char msg[1024];
        sprintf(msg, "%s: no image2", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else {
        int width = image1->GetWidth();
        int height = image1->GetHeight() + image2->GetHeight();
        int temp = image1->GetHeight();

        if (image1->GetWidth() != image2->GetWidth()) {
            char msg[1024];
            sprintf(msg, "%s: widths must match: %d, %d", SinkName(), image1->GetWidth(), image2->GetWidth());
            DataFlowException e(SinkName(), msg);
            throw e;
        }
        else {
            Pixel *pixel = new Pixel[width*height];

            image.SetWidth(width);
            image.SetHeight(height);
            image.SetBuffer(pixel);

            for(int i = 0; i < width; i++) {
                for(int j = 0; j < temp; j++) {
                    Pixel topPixel = image1->GetSinglePixel(i, j);
                    Pixel botPixel = image2->GetSinglePixel(i, j);
                    image.SetSinglePixel(i, j, topPixel);
                    image.SetSinglePixel(i, j+temp, botPixel);
                }
            }
        }
    }
}

void Blender::Execute() {
    if (image1 == nullptr) {
        char msg[1024];
        sprintf(msg, "%s: no image1", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else if(factor > 1.0) {
        char msg[1024];
        sprintf(msg, "%s: factor must be less than 1, is: %f", SinkName(), factor);
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else if(factor < 0.0) {
        char msg[1024];
        sprintf(msg, "%s: factor must be greater than 0, is: %f", SinkName(), factor);
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else {
        int width = image1->GetWidth();
        int height = image1->GetHeight();

        Pixel *pixel = new Pixel[width*height];

        image.SetWidth(width);
        image.SetHeight(height);
        image.SetBuffer(pixel);

        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; j++) {
                Pixel pixel1 = image1->GetSinglePixel(i, j);
                Pixel pixel2 = image2->GetSinglePixel(i, j);
                Pixel pixel3 = {
                    (unsigned char)((factor*pixel1.r) + ((1-factor)*pixel2.r)), 
                    (unsigned char)((factor*pixel1.g) + ((1-factor)*pixel2.g)), 
                    (unsigned char)((factor*pixel1.b) + ((1-factor)*pixel2.b))
                };
                image.SetSinglePixel(i, j, pixel3);
            }
        }
    }
}

