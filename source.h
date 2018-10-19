// CIS 330
// Project 3D
//
// Samuel Svindland
// 951472606
// ssvindla@cs.uoregon.edu
//
#include "image.h"
#include "logging.h"

#ifndef SOURCE_H
#define SOURCE_H

class Source {
    public:
        Source();
        Image *GetOutput();
        virtual void Update();
        virtual const char *SourceName() = 0;
    protected:
        virtual void Execute() = 0;
        Image image;
};

#endif