#include "image.h"
#include "stb_image.h"
#include "stb_image_write.h"

Image::Image(std::string file_path)
{
    const char *c_file_path = file_path.c_str();
    FILE *fp = fopen(c_file_path, "r");
    if (!fp)
    {
        throw std::filesystem::filesystem_error("Image::Image problem opening file", std::error_code());
    }
    scanhead(fp, &width, &height);
    rgb_image = stbi_load(c_file_path, &width, &height, &channels_in_file, 0);
    fclose(fp);
}

Image::Image(int width, int height)
    :width{width}
    ,height{height}
{
    // https://stackoverflow.com/questions/4010917/c-malloc-error-invalid-conversion-from-void-to-uint8-t
    // Last accessed [2024-08-17]
    // Doing this as I don't want to edit the header files I'm using for reading and writing images
    rgb_image = static_cast<uint8_t *>(malloc(width*height*channels_in_file)); 
}

Image::~Image()
{
    stbi_image_free(rgb_image);
}


// https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
// Last Accessed [2024-08-20]
Image::Image(Image img)
    :Image()
{
    std::swap(img);
    return *this;
}

Image::Image& operator=(Image img)
{
    swap(img);
    return *this;
}

Image::Image(Image&& img) noexcept
{
    std::swap(img);
    return *this;
}

Image::Image& operator=(Image&& img)
    :Image()
{
    std::swap(img);
}

void Image::swap(Image& img)
{
    std::swap(width, image.width);
    std::swap(height, image.height);
    std::swap(channels_in_file, img.channels_in_file);
    std::swap(jpeg_write_quality, img.jpeg_write_quality);
    std::swap(rgb_image, img.rgb_image);
}

int Image::write_to_file(std::string file_path)
{
    return stbi_write_jpg(file_path.c_str(), width, height, channels_in_file, rgb_image, jpeg_write_quality);
}

uint8_t& Image::loc(int i, int j)
{
    if (i >= height || j >= width || i < 0 || j < 0)
    {
        return 0;
    }
    return rgb_image[i * width + j];

}

// NOTE: I did not write the below, just copied it from the source in the below answer

// https://stackoverflow.com/questions/317140/get-dimensions-of-jpeg-in-c
// Last accessed [2024-08-11]

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

