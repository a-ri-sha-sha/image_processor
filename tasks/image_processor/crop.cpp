//
// Created by Arina Shaydeman on 21.03.2023.
//

#include "crop.h"
bool Crop::Apply(Bitmap* bitmap) {
    bitmap->Resize(height_, width_);
    return true;
}
Crop::Crop(uint32_t width, uint32_t height) {
    height_ = height;
    width_ = width;
}
