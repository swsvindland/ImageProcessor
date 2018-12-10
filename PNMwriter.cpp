// CIS 330
// Project 3D
//
// Samuel Svindland
// 951472606
// ssvindla@cs.uoregon.edu
//
#include <iostream>
#include <fstream>

#include "PNMwriter.h"

using namespace std;

void PNMwriter::Write(char *filename) {
    ofstream f_out;
    int width = image1->GetWidth();
    int height = image1->GetHeight();
    Pixel *pixel = image1->GetBuffer();

    f_out.open(filename, ios::binary);
    if(!f_out.is_open()) {
        cerr << "Could not open output file" << endl;
    }

    f_out << "P6\n" << width << " " << height << "\n" << 255;

    f_out.write((char *)pixel, width*height*sizeof(Pixel)+1);

    delete [] pixel;
    f_out.close();
}