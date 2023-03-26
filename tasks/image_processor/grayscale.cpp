//
// Created by Arina Shaydeman on 21.03.2023.
//

#include "grayscale.h"
bool Grayscale::Apply(Bitmap *bitmap) {
    const double red = 0.299;
    const double green = 0.587;
    const double blue = 0.114;
    for (size_t i = 0; i < bitmap->GetHeight(); ++i) {
        for (size_t j = 0; j < bitmap->GetWidth(); ++j) {
            unsigned char new_b = red * bitmap->GetPixels()(i, j).r + green * bitmap->GetPixels()(i, j).g +
                                  blue * bitmap->GetPixels()(i, j).b;
            unsigned char new_g = new_b;
            unsigned char new_r = new_b;
            bitmap->GetPixels()(i, j) = {new_b, new_g, new_r};
        }
    }
    return true;
}
