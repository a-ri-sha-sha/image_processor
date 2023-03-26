//
// Created by Arina Shaydeman on 21.03.2023.
//

#ifndef CPP_HSE_BITMAP_H
#define CPP_HSE_BITMAP_H

#include "tmatrix.h"
#include <cstdint>
#include <string>
#include <exception>
class BitmapException : public std::exception {
public:
    const char* what() const noexcept override {
        return message_.c_str();
    }
    explicit BitmapException(const std::string& message) : message_{message} {
    }

protected:
    std::string message_;
};

class Bitmap {
public:
    static const unsigned char UC255 = 255;
    static const unsigned char UC0 = 0;
    constexpr static const double D255 = 255.0;
    constexpr static const double D0 = 0.0;
    static const size_t SIZE_HEADER = 54;
    const size_t BIT_COUNT = 24;
    struct __attribute__((packed)) BmpHeader {
        char signature[2];
        uint32_t file_size;
        uint32_t reserved;
        uint32_t data_offset;
    };

    struct __attribute__((packed)) BmpInfo {  // deap header
        uint32_t info_size;
        int32_t width;
        int32_t height;
        uint16_t planes;
        uint16_t bit_count;
        uint32_t compression;
        uint32_t image_size;
        int32_t x_pixels_per_meter;
        int32_t y_pixels_per_meter;
        uint32_t colors_used;
        uint32_t colors_important;
    };
    struct __attribute__((packed)) RGB {
        unsigned char b;
        unsigned char g;
        unsigned char r;
    };
    struct RGBDouble {
        double b;
        double g;
        double r;

        explicit RGBDouble(const RGB& rgb);
        RGBDouble(const RGBDouble& rgb);

        RGBDouble& operator+=(const RGBDouble& lhv);
        RGBDouble& operator+=(const RGB& lhv);
        RGBDouble& operator-=(const RGBDouble& lhv);
        RGBDouble& operator-=(const RGB& lhv);
        RGBDouble& operator*=(const double lhv);

        RGBDouble operator+(const RGBDouble& lhv) const;
        RGBDouble operator+(const RGB& lhv) const;
        RGBDouble operator-(const RGBDouble& lhv) const;
        RGBDouble operator-(const RGB& lhv) const;
        RGBDouble operator*(const double lhv) const;

        explicit operator RGB() const;
    };

public:
    void ReadHeader(std::ifstream& file);
    void ReadInfo(std::ifstream& file);
    void ReadPixels(std::ifstream& file);

public:
    explicit Bitmap(const std::string& filename);
    Bitmap(const Bitmap& bitmap);
    void Output(const std::string& filename);
    TMatrix<Bitmap::RGB>& GetPixels();
    void Resize(uint32_t height, uint32_t width);
    uint32_t GetHeight() const;
    uint32_t GetWidth() const;

protected:
    BmpHeader header_;
    BmpInfo info_;
    TMatrix<RGB> pixels_;
};

#endif  // CPP_HSE_BITMAP_H
