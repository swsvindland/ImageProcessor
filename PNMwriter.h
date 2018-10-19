// CIS 330
// Project 3D
//
// Samuel Svindland
// 951472606
// ssvindla@cs.uoregon.edu
//
#include "image.h"
#include "sink.h"

#ifndef PNMWRITER_H
#define PNMWRITER_H

class PNMwriter : public Sink {
    public:
        void Write(char *);
        const char *SinkName() {return (const char *)"PNMwriter";};
};

#endif