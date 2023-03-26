//
// Created by Arina Shaydeman on 23.03.2023.
//
#include "creators.h"
#include "crop.h"
#include "negative.h"
#include "grayscale.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "mirror.h"
Filter* Creators::CreateCropFilter(const FilterDescription& fd) {
    if (fd.params_.size() > 2) {
        throw ParamsError("Too many parameters!");
    }
    if (fd.params_.size() < 2) {
        throw ParamsError("Not enough parameters!");
    }
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
    if (fd.params_.size() > 1) {
        throw ParamsError("Too many parameters!");
    }
    if (fd.params_.empty()) {
        throw ParamsError("Not enough parameters!");
    }
    return new EdgeDetection(atof(fd.params_[0]));
}
Filter* Creators::CreateMirrorFilter(const FilterDescription& fd) {
    return new Mirror;
}
