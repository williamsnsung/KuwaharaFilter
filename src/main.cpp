#include <string>
#include "image.h"

int main()
{
    std::string file_path = "../TestPhotos/ThisPersonDoesNotExist/thispersondoesnotexist.jpg";
    Image img (file_path);
    img.write_to_file("image.jpg");

    return 0;
}
