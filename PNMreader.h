// CIS 330
// Project 3D
//
// Samuel Svindland
// 951472606
// ssvindla@cs.uoregon.edu
//
#include "image.h"
#include "source.h"

#ifndef PNMREADER_H
#define PNMREADER_H

class PNMreader : public Source {
    public:
        PNMreader(char *);
        void Execute();
        const char *SourceName() {return (const char *)"PNMreader";};
    private:
        char *filename;
};

#endif