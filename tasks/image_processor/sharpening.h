//
// Created by Arina Shaydeman on 21.03.2023.
//

#ifndef CPP_HSE_SHARPENING_H
#define CPP_HSE_SHARPENING_H

#include "bitmap.h"
#include "matrix_filter.h"
class Sharpening : public MatrixFilter {
public:
    Sharpening();
    const TMatrix<double>& GetMatrix() override;
    bool Apply(Bitmap* bitmap) override;
    ~Sharpening() override{};

protected:
    TMatrix<double> matrix_;
};

#endif  // CPP_HSE_SHARPENING_H
