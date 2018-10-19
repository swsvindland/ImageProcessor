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

void Source::Update() {
    char msg[128];
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}