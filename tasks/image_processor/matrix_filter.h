//
// Created by Arina Shaydeman on 25.03.2023.
//

#ifndef CPP_HSE_MATRIX_FILTER_H
#define CPP_HSE_MATRIX_FILTER_H

#include "bitmap.h"
#include "filter.h"
class MatrixFilter : public Filter {
public:
    void ApllyMatrix(Bitmap& bitmap);
    virtual const TMatrix<double>& GetMatrix() = 0;
};

#endif  // CPP_HSE_MATRIX_FILTER_H
