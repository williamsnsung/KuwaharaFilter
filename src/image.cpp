#include "image.h"
// https://stackoverflow.com/questions/2076475/read-an-image-file-in-c-c-into-an-array
// Last accessed [2024-08-11]
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image(std::string file_path)
{
    const char* c_file_path = file_path.c_str();
    fp = fopen(c_file_path, "r");
    scanhead(fp, &width, &height);
    rgb_image = stbi_load(c_file_path, &width, &height, &channels_in_file, 0);
    fclose(fp);
}

Image::~Image()
{
    stbi_image_free(rgb_image);
}

int Image::write_to_file(std::string file_path)
{
    return stbi_write_jpg(file_path.c_str(), width, height, channels_in_file, rgb_image, jpeg_write_quality);
}


// https://stackoverflow.com/questions/317140/get-dimensions-of-jpeg-in-c
// Last accessed [2024-08-11]

/* portions derived from IJG code */

#define readbyte(a,b) do if(((a)=getc((b))) == EOF) return 0; while (0)
#define readword(a,b) do { int cc_=0,dd_=0; \
                              if((cc_=getc((b))) == EOF \
                                                      || (dd_=getc((b))) == EOF) return 0; \
                              (a) = (cc_<<8) + (dd_); \
                              } while(0)

int Image::scanhead(FILE *infile, int *image_width, int *image_height)
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

