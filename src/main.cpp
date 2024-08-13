#include <iostream>
#include <filesystem>
#include <cassert>
#include <fstream>

// https://stackoverflow.com/questions/2076475/read-an-image-file-in-c-c-into-an-array
// Last accessed [2024-08-11]
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <cstdio>
#include <stdio.h>

// https://stackoverflow.com/questions/317140/get-dimensions-of-jpeg-in-c
// Last accessed [2024-08-11]

/* portions derived from IJG code */

#define readbyte(a, b)                \
    do                                \
        if (((a) = getc((b))) == EOF) \
            return 0;                 \
    while (0)
#define readword(a, b)                                            \
    do                                                            \
    {                                                             \
        int cc_ = 0, dd_ = 0;                                     \
        if ((cc_ = getc((b))) == EOF || (dd_ = getc((b))) == EOF) \
            return 0;                                             \
        (a) = (cc_ << 8) + (dd_);                                 \
    } while (0)

int scanhead(FILE *infile, int *image_width, int *image_height)
{
    int marker = 0;
    int dummy = 0;
    if (getc(infile) != 0xFF || getc(infile) != 0xD8)
        return 0;

    for (;
         ;)
    {

        int discarded_bytes = 0;
        readbyte(marker, infile);
        while (marker != 0xFF)
        {
            discarded_bytes++;
            readbyte(marker, infile);
        }
        do
            readbyte(marker, infile);
        while (marker == 0xFF);

        if (discarded_bytes != 0)
            return 0;

        switch (marker)
        {
        case 0xC0:
        case 0xC1:
        case 0xC2:
        case 0xC3:
        case 0xC5:
        case 0xC6:
        case 0xC7:
        case 0xC9:
        case 0xCA:
        case 0xCB:
        case 0xCD:
        case 0xCE:
        case 0xCF:
        {
            readword(dummy, infile); /* usual parameter length count */
            readbyte(dummy, infile);
            readword((*image_height), infile);
            readword((*image_width), infile);
            readbyte(dummy, infile);

            return 1;
            break;
        }
        case 0xDA:
        case 0xD9:
            return 0;
        default:
        {
            int length;

            readword(length, infile);

            if (length < 2)
                return 0;
            length -= 2;
            while (length > 0)
            {
                readbyte(dummy, infile);
                length--;
            }
        }
        break;
        }
    }
}

// TODO create an RAII class to handle the loaded images from stb_image

int main()
{
    char* file_path = "../TestPhotos/ThisPersonDoesNotExist/thispersondoesnotexist.jpg";

    FILE *p = fopen(file_path, "r");
    int width, height, bpp;
    bpp = 3;

    scanhead(p, &width, &height);
    std::cout << width << " " << height;

    uint8_t *rgb_image = stbi_load(file_path, &width, &height, &bpp, 3);
    stbi_write_jpg("image.jpg", width, height, bpp, rgb_image, 100);
    stbi_image_free(rgb_image);
    return 0;
}
