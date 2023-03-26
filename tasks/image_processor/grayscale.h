//
// Created by Arina Shaydeman on 21.03.2023.
//

#ifndef CPP_HSE_GRAYSCALE_H
#define CPP_HSE_GRAYSCALE_H

#include "filter.h"
class Grayscale : public Filter {
public:
    bool Apply(Bitmap* bitmap) override;
    ~Grayscale() override{};
};
#endif  // CPP_HSE_GRAYSCALE_H
