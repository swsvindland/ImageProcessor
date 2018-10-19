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
        virtual void Update();
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

#endif