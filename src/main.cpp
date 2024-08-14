#include <string>
#include "image.h"

int main()
{
    std::string file_path = "../TestPhotos/ThisPersonDoesNotExist/thispersondoesnotexist.jpg";
    Image img (file_path);

    return 0;
}
