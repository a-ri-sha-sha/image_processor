//
// Created by Arina Shaydeman on 22.03.2023.
//

#include "pipeline.h"
void Pipeline::AddFilter(Filter* filter) {
    pipeline_.push_back(filter);
}
void Pipeline::Apply(Bitmap& bmp) {
    for (Filter* filter : pipeline_) {
        filter->Apply(&bmp);
    }
}
