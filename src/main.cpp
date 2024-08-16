#include <string>
#include "image.h"

int main()
{
    std::string file_path = "../TestPhotos/ThisPersonDoesNotExist/thispersondoesnotexist.jpg";
    Image img (file_path);
    std::cout << img.width << " " << img.height << "\n"; 
    std::cout << unsigned(img[0]) << "\n";
    img.write_to_file("image.jpg");

    return 0;
}
