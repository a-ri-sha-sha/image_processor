//
// Created by Arina Shaydeman on 22.03.2023.
//

#ifndef CPP_HSE_PARSER_H
#define CPP_HSE_PARSER_H

#include "filter_description.h"
#include "creators.h"
#include <string>
#include <iostream>

class Parser {
public:
    bool flag;
    Parser(int argc, char** argv) {
        if (argc == 1) {
            std::cerr << "Not enough parameters!" << std::endl;
            std::cerr << "Try to use: " << std::endl;
            std::cerr << "-crop v1 v2 \t v1 - int, width; v2 - int, height \t for cutting your picture" << std::endl;
            std::cerr << "-neg \t for application negative filter" << std::endl;
            std::cerr << "-gs \t for application grayscale filter" << std::endl;
            std::cerr << "-sharp \t for application sharpening filter" << std::endl;
            std::cerr << "-edge v1 \t v1 - double, sensitivity \t for application edge detection filter" << std::endl;
            std::cerr << "-mirror \t for application mirror filter" << std::endl;
            flag = false;
            return;
        }
        name_program_ = argv[0];
        input_ = argv[1];
        output_ = argv[2];
        flag = true;
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
