// https://stackoverflow.com/questions/2076475/read-an-image-file-in-c-c-into-an-array
// Last accessed [2024-08-11]
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <string>
#include "image.h"
#include <iostream>
#include "matrix.h"

Image get_image(const Matrix& r, const Matrix& g, const Matrix& b)
{
    Image res(r.X, r.Y);
    
    for (int i = 0; i < res.height; i++)
    {
        for (int j = 0; j < res.width; j++)
        {
            res.loc(i, j)[0] = static_cast<uint8_t>(r.loc(i,j));
            res.loc(i, j)[1] = static_cast<uint8_t>(g.loc(i,j));
            res.loc(i, j)[2] = static_cast<uint8_t>(b.loc(i,j));
        }
    }
    return res;
}

Matrix convolve(const Matrix& input, const Matrix& kernel)
{
    Matrix res(input.X, input.Y);
    int x, y;
    
    for (int i = 0; i < res.X; i++)
    {
        for (int j = 0; j < res.Y; j++)
        {
            x = i;
            y = j;
            if (x < 0)
                x == 0;
            if (x >= res.X)
                x = res.X - 1;
            if (y < 0)
                y = 0;
            if (y >= res.Y)
                y = res.Y - 1;
            for (int a = 0; a < kernel.X; a++)
            {
                for (int b = 0; b < kernel.Y; b++)
                {
                    // TODO
        }
    }

    return res;
}

int main()
{
    std::string file_path = "test.jpg";
    Image img(file_path);
    std::cout << img.width << " " << img.height << "\n"; 

    Matrix r(img.width, img.height);
    Matrix g(img.width, img.height);
    Matrix b(img.width, img.height);

    for (int i = 0; i < img.height; i++)
    {
        for (int j = 0; j < img.width; j++)
        {
            r.loc(i, j) = static_cast<double>(img.loc(i,j)[0]);
            g.loc(i, j) = static_cast<double>(img.loc(i,j)[1]);
            b.loc(i, j) = static_cast<double>(img.loc(i,j)[2]);
        }
    }

    Image res = get_image(r, g, b);

    res.write_to_file("image.jpg");

//    Image processed_image = kuwahara_filter(img);
    return 0;
}

