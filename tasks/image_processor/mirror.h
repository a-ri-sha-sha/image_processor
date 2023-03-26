//
// Created by Arina Shaydeman on 26.03.2023.
//

#ifndef CPP_HSE_MIRROR_H
#define CPP_HSE_MIRROR_H

#include "bitmap.h"
#include "filter.h"
class Mirror : public Filter {
public:
    bool Apply(Bitmap* bitmap) override;
    ~Mirror() override{};

protected:
    uint32_t height_;
    uint32_t width_;
};
#endif  // CPP_HSE_MIRROR_H
