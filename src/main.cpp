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
            x = i - static_cast<int>(kernel.X/2);
            y = j - static_cast<int>(kernel.Y/2);
            if (x < 0)
                x = 0;
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
                    int xn = x + a;
                    int yn = y + b;

                    res.loc(i,j) += input.loc(xn, yn) * kernel.loc(a,b);
                }
            }
        }
    }
    return res;
}

int main()
{
    std::string file_path = "grid.jpg";
    Image img(file_path);

    Matrix r(img.width, img.height);
    Matrix g(img.width, img.height);
    Matrix b(img.width, img.height);

    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            r.loc(i, j) = static_cast<double>(img.loc(i,j)[0]);
            g.loc(i, j) = static_cast<double>(img.loc(i,j)[1]);
            b.loc(i, j) = static_cast<double>(img.loc(i,j)[2]);
        }
    }
    
    Matrix Gx(3,3);
    Gx.loc(0,0) = 1;
    Gx.loc(0,1) = 0;
    Gx.loc(0,2) = -1;
    Gx.loc(1,0) = 2;
    Gx.loc(1,1) = 0;
    Gx.loc(1,2) = -2;
    Gx.loc(2,0) = 1;
    Gx.loc(2,1) = 0;
    Gx.loc(2,2) = -1;

    Matrix Gy(3,3);
    Gy.loc(0,0) = 1;
    Gy.loc(0,1) = 2;
    Gy.loc(0,2) = 1;
    Gy.loc(1,0) = 0;
    Gy.loc(1,1) = 0;
    Gy.loc(1,2) = 0;
    Gy.loc(2,0) = -1;
    Gy.loc(2,1) = -2;
    Gy.loc(2,2) = -1;

    Matrix rxSobel = convolve(r, Gx);
    Matrix rySobel = convolve(r, Gy);
    Matrix gxSobel = convolve(g, Gx);
    Matrix gySobel = convolve(g, Gy);
    Matrix bxSobel = convolve(b, Gx);
    Matrix bySobel = convolve(b, Gy);

    
    Matrix rSobel = rxSobel + rySobel;
    Matrix gSobel = gxSobel + gySobel;
    Matrix bSobel = bxSobel + bySobel;
/**
    for (int i = 0; i < img.height; i++)
    {
        for (int j = 0; j < img.width; j++)
        {
            rSobel.loc(i, j) = static_cast<int>(sqrt(rSobel.loc(i,j)));
            gSobel.loc(i, j) = static_cast<int>(sqrt(gSobel.loc(i,j)));
            bSobel.loc(i, j) = static_cast<int>(sqrt(bSobel.loc(i,j)));
        }
    }
*/
    Image res = get_image(rSobel, gSobel, bSobel);

    res.write_to_file("image.jpg");

//    Image processed_image = kuwahara_filter(img);
    return 0;
}

