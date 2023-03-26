//
// Created by Arina Shaydeman on 21.03.2023.
//

#include "edge_detection.h"
#include "bitmap.h"
#include "grayscale.h"
EdgeDetection::EdgeDetection(double threshold) {
    matrix_.Resize(3, 3);
    matrix_(1, 1) = 4;
    matrix_(0, 1) = -1;
    matrix_(1, 0) = -1;
    matrix_(1, 2) = -1;
    matrix_(2, 1) = -1;
    threshold_ = Bitmap::UC255 * threshold;
}
const TMatrix<double>& EdgeDetection::GetMatrix() {
    return matrix_;
}
bool EdgeDetection::Apply(Bitmap* bitmap) {
    Grayscale gr;
    gr.Apply(bitmap);
    ApllyMatrix(*bitmap);
    for (size_t i = 0; i < bitmap->GetHeight(); ++i) {
        for (size_t j = 0; j < bitmap->GetWidth(); ++j) {
            if (static_cast<double>(bitmap->GetPixels()(i, j).g) > threshold_) {
                bitmap->GetPixels()(i, j).r = Bitmap::UC255;
                bitmap->GetPixels()(i, j).g = Bitmap::UC255;
                bitmap->GetPixels()(i, j).b = Bitmap::UC255;
            } else {
                bitmap->GetPixels()(i, j).r = 0;
                bitmap->GetPixels()(i, j).g = 0;
                bitmap->GetPixels()(i, j).b = 0;
            }
        }
    }
    return true;
}
