// CIS 330
// Project 3D
//
// Samuel Svindland
// 951472606
// ssvindla@cs.uoregon.edu
//
#include <iostream>
#include <fstream>

#include "PNMreader.h"

using namespace std;

PNMreader::PNMreader(char *filename) {
    this->filename = filename;
}

void PNMreader::Execute() {
    ifstream f_in;
    string magicNum;
    int width, height, maxval;

    f_in.open(filename, ios::binary);
    if(!f_in.is_open()) {
        cerr << "Could not open input file" << endl;
        exit(1);
    }

    f_in >> magicNum >> width >> height >> maxval;

    if(magicNum != "P6") {
        cerr << "File not correct type. Must be .pnm (P6)" << endl;
        exit(1);
    }

    Pixel *pixel = new Pixel[width*height];

    f_in.read((char *)pixel, width*height*sizeof(Pixel)+1);

    image.SetWidth(width);
    image.SetHeight(height);
    image.SetBuffer(pixel);

    delete [] pixel;
    f_in.close();
}