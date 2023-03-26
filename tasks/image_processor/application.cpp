//
// Created by Arina Shaydeman on 23.03.2023.
//
#include "application.h"
#include "creators.h"
Application::Application(int argc, char** argv) : par_(argc, argv) {
    {
        argc_ = argc;
        argv_ = argv;
        produser_.insert({"-crop", &Creators::CreateCropFilter});
        produser_.insert({"-gs", &Creators::CreatGrayscaleFilter});
        produser_.insert({"-neg", &Creators::CreateNegativeFilter});
        produser_.insert({"-sharp", &Creators::CreateSharpingFilter});
        produser_.insert({"-edge", &Creators::CreateEdgeDetectionFilter});
        //        produser_.insert({"-blur", &Creators::CreateGaussianBlurFilter});
        for (const FilterDescription& filter_description : par_.GetFiltersDescription()) {
            pipeline_.AddFilter(GetFilter(filter_description));
        }
    }
}
Filter* Application::GetFilter(const FilterDescription& fd) {
    return produser_.at(fd.name_)(fd);
}
void Application::Run() {
    if (par_.flag) {
        Bitmap bitmap(par_.GetInput());
        pipeline_.Apply(bitmap);
        bitmap.Output(par_.GetOutput());
    }
}
