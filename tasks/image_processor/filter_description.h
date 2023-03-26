//
// Created by Arina Shaydeman on 22.03.2023.
//

#ifndef CPP_HSE_FILTER_DESCRIPTION_H
#define CPP_HSE_FILTER_DESCRIPTION_H

#include <vector>
class FilterDescription {
public:
    FilterDescription(const char* name, const std::vector<char*> params) {
        name_ = name;
        params_ = params;
    }
    const char* name_;
    std::vector<char*> params_;
};

#endif  // CPP_HSE_FILTER_DESCRIPTION_H
