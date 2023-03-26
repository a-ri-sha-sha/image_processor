//
// Created by Arina Shaydeman on 21.03.2023.
//

#ifndef CPP_HSE_CROP_H
#define CPP_HSE_CROP_H

#include "filter.h"
class Crop : public Filter {
public:
    Crop(uint32_t height, uint32_t width);
    bool Apply(Bitmap* bitmap) override;
    ~Crop() override{};

protected:
    uint32_t height_;
    uint32_t width_;
};

#endif  // CPP_HSE_CROP_H
