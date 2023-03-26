//
// Created by Arina Shaydeman on 26.03.2023.
//

#include "mirror.h"
bool Mirror::Apply(Bitmap *bitmap) {
    TMatrix<Bitmap::RGB> new_pixels(bitmap->GetPixels());
    size_t width = bitmap->GetWidth();
    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < width; ++j) {
            new_pixels(i, width - j - 1) = bitmap->GetPixels()(i, j);
        }
    }
    new_pixels.Swap(new_pixels, bitmap->GetPixels());
    return true;
}
