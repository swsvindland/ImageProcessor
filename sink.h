// CIS 330
// Project 3D
//
// Samuel Svindland
// 951472606
// ssvindla@cs.uoregon.edu
//
#include "image.h"
#include "logging.h"

#ifndef SINK_H
#define SINK_H

class Sink {
    public:
        Sink();
        void SetInput(Image *);
        void SetInput2(Image *);
        virtual const char *SinkName() = 0;
    protected:
        Image *image1;
        Image *image2;
};

#endif