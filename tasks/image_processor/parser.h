//
// Created by Arina Shaydeman on 22.03.2023.
//

#ifndef CPP_HSE_PARSER_H
#define CPP_HSE_PARSER_H

#include "filter_description.h"
#include <string>

class Parser {
public:
    Parser(int argc, char** argv) {
        name_program_ = argv[0];
        input_ = argv[1];
        output_ = argv[2];
        char* name = nullptr;
        std::vector<char*> params;
        for (int i = 3; i < argc; ++i) {
            if (i == 3 && argv[i][0] == '-') {
                name = argv[i];
            } else if (i != 3 && argv[i][0] == '-') {
                filter_description_.push_back(FilterDescription(name, params));
                params.clear();
                name = argv[i];
            } else {
                params.push_back(argv[i]);
            }
            if (i == argc - 1) {
                filter_description_.push_back(FilterDescription(name, params));
            }
        }
    }
    std::string GetInput() {
        return input_;
    };
    std::string GetOutput() {
        return output_;
    }
    std::vector<FilterDescription> GetFiltersDescription() {
        return filter_description_;
    }

protected:
    std::string name_program_;
    std::string input_;
    std::string output_;
    std::vector<FilterDescription> filter_description_;
};
#endif  // CPP_HSE_PARSER_H
