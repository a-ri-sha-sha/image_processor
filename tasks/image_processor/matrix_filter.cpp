//
// Created by Arina Shaydeman on 25.03.2023.
//

#include "matrix_filter.h"
void MatrixFilter::ApllyMatrix(Bitmap& bitmap) {
    TMatrix<double> matrix = GetMatrix();
    TMatrix<Bitmap::RGB> new_pixels = bitmap.GetPixels();
    for (size_t i = 0; i < bitmap.GetHeight(); ++i) {
        for (size_t j = 0; j < bitmap.GetWidth(); ++j) {
            Bitmap::RGBDouble pixel({0, 0, 0});
            for (size_t y = 0; y < 3; ++y) {
                for (size_t x = 0; x < 3; ++x) {
                    if (i + y > 0 && i + y < bitmap.GetHeight() + 1 && j + x > 0 && j + x < bitmap.GetWidth() + 1) {
                        Bitmap::RGBDouble new_pixel(bitmap.GetPixels()(i + y - 1, j + x - 1));
                        pixel += new_pixel * matrix(y, x);
                    } else {
                        Bitmap::RGBDouble new_pixel(bitmap.GetPixels()(i, j));
                        pixel += new_pixel * matrix(y, x);
                    }
                }
            }
            new_pixels(i, j) = static_cast<Bitmap::RGB>(pixel);
        }
    }
    new_pixels.Swap(new_pixels, bitmap.GetPixels());
}
