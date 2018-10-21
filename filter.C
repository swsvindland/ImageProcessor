// CIS 330
// Project 3D
//
// Samuel Svindland
// 951472606
// ssvindla@cs.uoregon.edu
//

#include "filter.h"

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
        delete [] pixel;
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
            delete [] pixel;
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
            delete [] pixel;
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
        delete [] pixel;
    }
}

void Mirror::Execute() {
    if (image1 == nullptr) {
        char msg[1024];
        sprintf(msg, "%s: no image1", SinkName());
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
                Pixel new_pixel = image1->GetSinglePixel(i, j);
                image.SetSinglePixel(width-i, j, new_pixel);
            }
        }
        delete [] pixel;
    }
}

void Rotate::Execute() {
    if (image1 == nullptr) {
        char msg[1024];
        sprintf(msg, "%s: no image1", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else {
        int width = image1->GetWidth();
        int height = image1->GetHeight();

        Pixel *pixel = new Pixel[width*height];

        image.SetWidth(height);
        image.SetHeight(width);
        image.SetBuffer(pixel); 

        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; j++) {
                Pixel pixel = image1->GetSinglePixel(i, j);
                image.SetSinglePixel(height-j, i, pixel);
            }
        }
        delete [] pixel;
    }
}

void Subtract::Execute() {
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
        if(image1->GetHeight() != image2->GetHeight()) {
            char msg[1024];
            sprintf(msg, "%s: height must match: %d, %d", SinkName(), image1->GetHeight(), image2->GetHeight());
            DataFlowException e(SinkName(), msg);
            throw e;
        }
        else if(image1->GetWidth() != image2->GetWidth()) {
            char msg[1024];
            sprintf(msg, "%s: width must match: %d, %d", SinkName(), image1->GetWidth(), image2->GetWidth());
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

                    unsigned char r, g, b;

                    if (pixel1.r > pixel2.r) {
                        r = pixel1.r - pixel2.r;
                    }
                    else {
                        r = 0;
                    }
                    if (pixel1.g > pixel2.g) {
                        g = pixel1.g - pixel2.g;
                    }
                    else {
                        g = 0;
                    }
                    if (pixel1.b > pixel2.b) {
                        b = pixel1.b - pixel2.b;
                    }
                    else {
                        b = 0;
                    }
                    Pixel pixel3 = {r, g, b};
                    image.SetSinglePixel(i, j, pixel3);
                }
            }
            delete [] pixel;
        }
    }
}

void Grayscale::Execute() {
    if (image1 == nullptr) {
        char msg[1024];
        sprintf(msg, "%s: no image1", SinkName());
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

                unsigned char p = (int)pixel1.r / 5 + (int)pixel1.g / 2 + (int)pixel1.b / 4;

                Pixel pixel2 = {p, p, p};

                image.SetSinglePixel(i, j, pixel2);
            }
        }
        delete [] pixel;
    } 
}

void Blur::Execute() {
        if (image1 == nullptr) {
        char msg[1024];
        sprintf(msg, "%s: no image1", SinkName());
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
                if(i == 0 || j == 0 || i == width-1 || j == height-1) {
                    Pixel pixel0 = image1->GetSinglePixel(i, j);
                    image.SetSinglePixel(i, j, pixel0);
                }
                else {
                    Pixel pixel1 = image1->GetSinglePixel(i-1, j-1);
                    Pixel pixel2 = image1->GetSinglePixel(i, j-1);
                    Pixel pixel3 = image1->GetSinglePixel(i+1, j-1);
                    Pixel pixel4 = image1->GetSinglePixel(i-1, j);
                    Pixel pixel5 = image1->GetSinglePixel(i+1, j);
                    Pixel pixel6 = image1->GetSinglePixel(i-1, j+1);
                    Pixel pixel7 = image1->GetSinglePixel(i, j+1);
                    Pixel pixel8 = image1->GetSinglePixel(i+1, j+1);

                    unsigned char r = ((int)pixel1.r / 8 + (int)pixel2.r / 8 + (int)pixel3.r / 8 + (int)pixel4.r / 8 + (int)pixel5.r / 8 + (int)pixel6.r / 8 + (int)pixel7.r / 8 + (int)pixel8.r / 8);
                    unsigned char g = ((int)pixel1.g / 8 + (int)pixel2.g / 8 + (int)pixel3.g / 8 + (int)pixel4.g / 8 + (int)pixel5.g / 8 + (int)pixel6.g / 8 + (int)pixel7.g / 8 + (int)pixel8.g / 8); 
                    unsigned char b = ((int)pixel1.b / 8 + (int)pixel2.b / 8 + (int)pixel3.b / 8 + (int)pixel4.b / 8 + (int)pixel5.b / 8 + (int)pixel6.b / 8 + (int)pixel7.b / 8 + (int)pixel8.b / 8);
                    
                    Pixel pixel9 = {r, g, b};
                    
                    image.SetSinglePixel(i, j, pixel9);
                }
            }
        }
        delete [] pixel;
    }
}

Color::Color(int width, int height, unsigned char r, unsigned char g, unsigned char b) {
    this->width = width;
    this->height = height;
    this->r = r;
    this->g = g;
    this->b = b;
    Execute();
}

void Color::Execute() {
    Pixel *pixel = new Pixel[width*height];

    image.SetWidth(width);
    image.SetHeight(height);
    image.SetBuffer(pixel); 

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            Pixel pixel1 = {r, g, b};
            image.SetSinglePixel(i, j, pixel1);
        }
    }
    delete [] pixel;
}

void CheckSum::OutputCheckSum(char *filename) {
    FILE *f_out;

    f_out = fopen(filename, "w");
    if(f_out == NULL) {
        fprintf(stderr, "Could not open checksum file\n");
        exit(1);
    }

    int width = image1->GetWidth();
    int height = image1->GetHeight();

    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            Pixel pixel = image1->GetSinglePixel(i, j);
            r += pixel.r;
            g += pixel.g;
            b += pixel.b;
        }
    }

    fprintf(f_out, "CHECKSUM: %d, %d, %d\n", r, g, b);
}
