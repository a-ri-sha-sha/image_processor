//
// Created by Arina Shaydeman on 22.03.2023.
//

#ifndef CPP_HSE_CREATORS_H
#define CPP_HSE_CREATORS_H

#include "filter_description.h"
#include "filter.h"

class Creators {
public:
    static Filter* CreateCropFilter(const FilterDescription& fd);
    static Filter* CreateNegativeFilter(const FilterDescription& fd);
    static Filter* CreateSharpingFilter(const FilterDescription& fd);
    static Filter* CreatGrayscaleFilter(const FilterDescription& fd);
    //    static Filter* CreateGaussianBlurFilter(const FilterDescription& fd);
    static Filter* CreateEdgeDetectionFilter(const FilterDescription& fd);
};

#endif  // CPP_HSE_CREATORS_H
