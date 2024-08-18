#include <vector>
#include "image.h"
#include "stb_image.h"
#include "stb_image_write.h"

std::vector<uint8_t> fill_quadrant(const Image& img, quadrant_size, start_i, start_j)
{
    std::vector<uint8_t> res;
    for (int i = start_i; i < quadrant_size < i++)
    {
        for (int j = start_j; j < quadrant_size < j++)
        {
           res.push_back(img.loc(i, j)); 
        }
    }
    return res;
}

Image kuwahara_filter(const Image& img, int quadrant_size)
{
    std::vector<uint8_t> quadrant_1(quadrant_size * quadrant_size); 
    std::vector<uint8_t> quadrant_2(quadrant_size * quadrant_size); 
    std::vector<uint8_t> quadrant_3(quadrant_size * quadrant_size); 
    std::vector<uint8_t> quadrant_4(quadrant_size * quadrant_size); 

    Image processed_image(img.width, img.height);
    for (int i = 0; i < img.height; i++)
    {
        for (int j = 0; j < img.width; j++)
        {
            quadrant_1 = fill_quadrant(img, quadrant_size, i - quadrant_size + 1, j - quadrant_size + 1);
            quadrant_2 = fill_quadrant(img, quadrant_size, i, j - quadrant_size + 1);
            quadrant_3 = fill_quadrant(img, quadrant_size, i - quadrant_size + 1, j);
            quadrant_4 = fill_quadrant(img, quadrant_size, i, j);
            // TODO
        }
    }
    return processed_image;
}
