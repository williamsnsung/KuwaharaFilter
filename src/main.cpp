#include <iostream>
#include <filesystem>
#include <cassert>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// TODO create an RAII class to handle the loaded images from stb_image

int main() {
    std::filesystem::path f = "../TestPhotos/MyPhotos/IMG_0398.jpeg";
    assert(std::filesystem::exists(f));
    if (std::filesystem::is_regular_file(f))
        std::cout << f << "is a file; its size is " << std::filesystem::file_size(f) << '\n';

}
