//
// Created by Arina Shaydeman on 23.03.2023.
//
#include "creators.h"
#include "crop.h"
#include "negative.h"
#include "grayscale.h"
#include "sharpening.h"
#include "edge_detection.h"
Filter* Creators::CreateCropFilter(const FilterDescription& fd) {
    return new Crop(atoi(fd.params_[0]), atoi(fd.params_[1]));
}
Filter* Creators::CreateNegativeFilter(const FilterDescription& fd) {
    return new Negative();
}
Filter* Creators::CreatGrayscaleFilter(const FilterDescription& fd) {
    return new Grayscale();
}
Filter* Creators::CreateSharpingFilter(const FilterDescription& fd) {
    return new Sharpening();
}
Filter* Creators::CreateEdgeDetectionFilter(const FilterDescription& fd) {
    return new EdgeDetection(atof(fd.params_[0]));
}
