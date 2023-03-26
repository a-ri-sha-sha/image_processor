//
// Created by Arina Shaydeman on 21.03.2023.
//

#include "negative.h"
#include "bitmap.h"
bool Negative::Apply(Bitmap* bitmap) {
    for (size_t i = 0; i < bitmap->GetHeight(); ++i) {
        for (size_t j = 0; j < bitmap->GetWidth(); ++j) {
            unsigned char new_b = Bitmap::UC255 - bitmap->GetPixels()(i, j).b;
            unsigned char new_g = Bitmap::UC255 - bitmap->GetPixels()(i, j).g;
            unsigned char new_r = Bitmap::UC255 - bitmap->GetPixels()(i, j).r;
            bitmap->GetPixels()(i, j) = {new_b, new_g, new_r};
        }
    }
    return true;
}