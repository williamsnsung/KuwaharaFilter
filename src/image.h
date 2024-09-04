#ifndef IMAGE_H
#define IMAGE_H

#include <algorithm>
#include <cstdio>
#include <stdexcept>
#include <filesystem>
#include "stb_image.h"
#include "stb_image_write.h"
class Image {
    public:
        // TODO grab number of channels and color model
        int width, height, channels_in_file = 3, jpeg_write_quality = 100;

        Image(std::string file_path);
        Image(int width, int height);
        ~Image();

        Image(const Image& img);
        Image& operator=(const Image& img);

        Image(Image&& img) noexcept;
        Image& operator=(Image&& img);

        void swap(Image& img);

        int write_to_file(std::string file_path);
        uint8_t* loc(int i, int j); // height rows of width pixels

    private:
        uint8_t* rgb_image;
        uint8_t EDGE_PIXEL_VALUE = 0;

        bool readbyte(int a, FILE *b);
        bool readword(int a, FILE *b);
        int scanhead(FILE *infile, int *image_width, int *image_height);
};

#endif
