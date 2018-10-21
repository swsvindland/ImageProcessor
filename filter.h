// CIS 330
// Project 3D
//
// Samuel Svindland
// 951472606
// ssvindla@cs.uoregon.edu
//
#ifndef FILTER_H
#define FILTER_H

#include "image.h"
#include "source.h"
#include "sink.h"
#include "logging.h"

class Filter : public Source, public Sink {
    public:
        virtual const char *FilterName() = 0;
        const char *SourceName() {return FilterName();};
        const char *SinkName() {return FilterName();};
};

class Shrinker : public Filter {
    public:
        void Execute();
        const char *FilterName() {return (const char *)"Shrinker";};
};

class LRCombine : public Filter {
    public:
        void Execute();
        const char *FilterName() {return (const char *)"LRCombine";};
};

class TBCombine : public Filter {
    public:
        void Execute();
        const char *FilterName() {return (const char *)"TBCombine";};
};

class Blender : public Filter {
    public:
        void Execute();
        void SetFactor(double factor) {this->factor = factor;};
        double factor;
        const char *FilterName() {return (const char *)"Blender";};
};

class Mirror : public Filter {
    public:
        void Execute();
        const char *FilterName() {return (const char *)"Mirror";};
};

class Rotate : public Filter {
    public:
        void Execute();
        const char *FilterName() {return (const char *)"Rotate";};
};

class Subtract : public Filter {
    public:
        void Execute();
        const char *FilterName() {return (const char *)"Subtract";};
};

class Grayscale : public Filter {
    public:
        void Execute();
        const char *FilterName() {return (const char *)"Grayscale";};
};

class Blur : public Filter {
    public:
        void Execute();
        const char *FilterName() {return (const char *)"Blur";};
};

class Color: public Source {
    public:
        Color(int, int, unsigned char, unsigned char, unsigned char);
        void Execute();
        const char *SourceName() {return (const char *)"Color";};
    private:
        int width, height;
        unsigned char r, g, b;
};

class CheckSum: public Sink {
    public:
        void OutputCheckSum(char *);
        const char *SinkName() {return (const char *)"CheckSum";};
};

#endif