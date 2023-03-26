//
// Created by Arina Shaydeman on 22.03.2023.
//

#ifndef CPP_HSE_PIPELINE_H
#define CPP_HSE_PIPELINE_H

#include <vector>
#include "bitmap.h"
#include "filter.h"

class Pipeline {
public:
    void Apply(Bitmap& bmp);
    void AddFilter(Filter* filter);
    ~Pipeline();

protected:
    std::vector<Filter*> pipeline_;
};

#endif  // CPP_HSE_PIPELINE_H
