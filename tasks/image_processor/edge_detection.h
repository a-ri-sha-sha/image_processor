//
// Created by Arina Shaydeman on 21.03.2023.
//

#ifndef CPP_HSE_EDGE_DETECTION_H
#define CPP_HSE_EDGE_DETECTION_H

#include "bitmap.h"
#include "matrix_filter.h"
class EdgeDetection : public MatrixFilter {
public:
    explicit EdgeDetection(double threshold);
    const TMatrix<double>& GetMatrix() override;
    bool Apply(Bitmap* bitmap) override;

protected:
    TMatrix<double> matrix_;
    double threshold_;
};
#endif  // CPP_HSE_EDGE_DETECTION_H
