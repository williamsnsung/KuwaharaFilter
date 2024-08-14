#ifndef IMAGE_H
#define IMAGE_H

// https://stackoverflow.com/questions/2076475/read-an-image-file-in-c-c-into-an-array
// Last accessed [2024-08-11]
#include <cstdio>
#include <iostream>

class Image {
    public:
        Image(std::string file_path);
        ~Image();

    private:
        FILE *fp;

        bool readbyte(int a, FILE *b);
        bool readword(int a, FILE *b);
        int scanhead(FILE *infile, int *image_width, int *image_height);
};

#endif
