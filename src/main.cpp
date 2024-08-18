#include <string>
#include "image.h"
#include <iostream>
// https://stackoverflow.com/questions/2076475/read-an-image-file-in-c-c-into-an-array
// Last accessed [2024-08-11]
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

int main()
{
    std::string file_path = "../TestPhotos/ThisPersonDoesNotExist/thispersondoesnotexist.jpg";
    Image img(file_path);
    std::cout << img.width << " " << img.height << "\n"; 
    std::cout << unsigned(img.loc(0,0)) << "\n";
    img.write_to_file("image.jpg");

    Image processed_image = kuwahara_filter(img);
    return 0;
}

