//
// Created by Arina Shaydeman on 22.03.2023.
//

#ifndef CPP_HSE_APPLICATION_H
#define CPP_HSE_APPLICATION_H
#include <map>
#include "parser.h"
#include "filter.h"
class Application {
public:
    Application(int argc, char** argv);
    Filter* GetFilter(const FilterDescription& fd);

protected:
    Parser par_;
    using PtrToFd = Filter* (*)(const FilterDescription& filter);
    std::map<std::string_view, PtrToFd> produser_;
    int argc_;
    char** argv_;
};
#endif  // CPP_HSE_APPLICATION_H
