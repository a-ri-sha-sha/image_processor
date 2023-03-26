//
// Created by Arina Shaydeman on 21.03.2023.
//

#ifndef CPP_HSE_FILTER_H
#define CPP_HSE_FILTER_H

#include "bitmap.h"

class Filter {
public:
    virtual bool Apply(Bitmap*) = 0;
    virtual ~Filter();
};

#endif  // CPP_HSE_FILTER_H
