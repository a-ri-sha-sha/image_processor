//
// Created by Arina Shaydeman on 21.03.2023.
//

#include "sharpening.h"
#include "bitmap.h"

Sharpening::Sharpening() {
    const double five = 5;
    matrix_.Resize(3, 3);
    matrix_(1, 1) = five;
    matrix_(0, 1) = -1;
    matrix_(1, 0) = -1;
    matrix_(1, 2) = -1;
    matrix_(2, 1) = -1;
}

const TMatrix<double>& Sharpening::GetMatrix() {
    return matrix_;
}

bool Sharpening::Apply(Bitmap* bitmap) {
    ApllyMatrix(*bitmap);
    return true;
}
