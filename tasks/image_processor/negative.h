//
// Created by Arina Shaydeman on 21.03.2023.
//

#ifndef CPP_HSE_NEGATIVE_H
#define CPP_HSE_NEGATIVE_H

#include "bitmap.h"
#include "filter.h"
class Negative : public Filter {
public:
    bool Apply(Bitmap* bitmap) override;
    ~Negative() override{};
};
#endif  // CPP_HSE_NEGATIVE_H
