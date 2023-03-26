//
// Created by Arina Shaydeman on 21.03.2023.
//

#include <fstream>
#include <iostream>
#include <filesystem>
#include <memory>
#include "bitmap.h"

Bitmap::Bitmap(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {  // TODO: сделать проверку заранее
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }
    file.read(reinterpret_cast<char*>(&header_), sizeof(header_));
    file.read(reinterpret_cast<char*>(&info_), sizeof(info_));
    //    if (header_.signature[0] != 'B' || header_.signature[1] != 'M') {
    //        std::cerr << "Not a BMP file: " << filename << std::endl;
    //        return;
    //    }
    //    if (info_.info_size != sizeof(BmpInfo)) {
    //        std::cerr << "Invalid BMP format: " << filename << std::endl;
    //        return;
    //    }
    //    if (info_.bit_count != 24) {
    //        std::cerr << "Only 24-bit BMPs are supported: " << filename << std::endl;
    //        return;
    //    }
    //    if (info_.compression != 0) {
    //        std::cerr << "Compressed BMPs are not supported: " << filename << std::endl;
    //        return;
    //    }
    //    if (info_.colors_used != 0 || info_.colors_important != 0) {
    //        std::cerr << "BMPs with color tables are not supported: " << filename << std::endl;
    //        return;
    //    }
    int32_t width = info_.width;
    int32_t height = info_.height;
    pixels_.Resize(width, height);
    for (int32_t y = info_.height - 1; y >= 0; --y) {
        for (int32_t x = 0; x < info_.width; ++x) {
            uint8_t b = 0;
            uint8_t g = 0;
            uint8_t r = 0;
            file.read(reinterpret_cast<char*>(&b), sizeof(b));
            file.read(reinterpret_cast<char*>(&g), sizeof(g));
            file.read(reinterpret_cast<char*>(&r), sizeof(r));
            pixels_(y, x) = RGB{b, g, r};
        }

        // заглушка для выравнивания строк по границе 4-х байт
        uint8_t padding = 0;  // seekg(кол-во байт смещения, смещение)
        // skip padding
        for (int32_t i = 0; i < (4 - ((info_.width * sizeof(RGB)) % 4)) % 4; i++) {
            file.read(reinterpret_cast<char*>(&padding), sizeof(padding));
        }
    }
    file.close();
}
void Bitmap::Output(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }
    file.write(reinterpret_cast<char*>(&header_), sizeof(header_));
    file.write(reinterpret_cast<char*>(&info_), sizeof(info_));
    for (int32_t y = info_.height - 1; y >= 0; y--) {
        for (int32_t x = 0; x < info_.width; x++) {
            uint8_t b = pixels_(y, x).b;
            uint8_t g = pixels_(y, x).g;
            uint8_t r = pixels_(y, x).r;
            file.write(reinterpret_cast<char*>(&b), sizeof(b));
            file.write(reinterpret_cast<char*>(&g), sizeof(g));
            file.write(reinterpret_cast<char*>(&r), sizeof(r));
        }

        // заглушка для выравнивания строк по границе 4-х байт
        uint8_t padding = 0;
        for (int32_t i = 0; i < (4 - ((info_.width * sizeof(RGB)) % 4)) % 4; i++) {
            file.write(reinterpret_cast<char*>(&padding), sizeof(padding));
        }
    }
    file.close();
}
TMatrix<Bitmap::RGB>& Bitmap::GetPixels() {
    return pixels_;
}
void Bitmap::Resize(uint32_t height, uint32_t width) {
    pixels_.Resize(width, height);
    info_.width = static_cast<int32_t>(width);
    info_.height = static_cast<int32_t>(height);
    header_.file_size = SIZE_HEADER + width * height * 3;  // TODO: magic number
}
uint32_t Bitmap::GetHeight() const {
    return info_.height;
}
uint32_t Bitmap::GetWidth() const {
    return info_.width;
}
Bitmap::Bitmap(const Bitmap& bitmap) {
    info_ = bitmap.info_;
    pixels_ = bitmap.pixels_;
    header_ = bitmap.header_;
}
Bitmap::RGBDouble::RGBDouble(const Bitmap::RGB& rgb) {
    b = static_cast<double>(rgb.b);
    g = static_cast<double>(rgb.g);
    r = static_cast<double>(rgb.r);
}
Bitmap::RGBDouble::RGBDouble(const Bitmap::RGBDouble& rgb) {
    b = rgb.b;
    g = rgb.g;
    r = rgb.r;
}
Bitmap::RGBDouble& Bitmap::RGBDouble::operator+=(const Bitmap::RGBDouble& lhv) {
    b += lhv.b;
    g += lhv.g;
    r += lhv.r;
    return *this;
}
Bitmap::RGBDouble& Bitmap::RGBDouble::operator+=(const Bitmap::RGB& lhv) {
    b += static_cast<double>(lhv.b);
    g += static_cast<double>(lhv.g);
    r += static_cast<double>(lhv.r);
    return *this;
}
Bitmap::RGBDouble& Bitmap::RGBDouble::operator-=(const Bitmap::RGBDouble& lhv) {
    b -= lhv.b;
    g -= lhv.g;
    r -= lhv.r;
    return *this;
}
Bitmap::RGBDouble& Bitmap::RGBDouble::operator-=(const Bitmap::RGB& lhv) {
    b -= static_cast<double>(lhv.b);
    g -= static_cast<double>(lhv.g);
    r -= static_cast<double>(lhv.r);
    return *this;
}
Bitmap::RGBDouble& Bitmap::RGBDouble::operator*=(const double lhv) {
    b *= lhv;
    g *= lhv;
    r *= lhv;
    return *this;
}
Bitmap::RGBDouble Bitmap::RGBDouble::operator+(const Bitmap::RGBDouble& lhv) const {
    RGBDouble ans(*this);
    ans += lhv;
    return ans;
}
Bitmap::RGBDouble Bitmap::RGBDouble::operator+(const Bitmap::RGB& lhv) const {
    RGBDouble ans(*this);
    ans += lhv;
    return ans;
}
Bitmap::RGBDouble Bitmap::RGBDouble::operator-(const Bitmap::RGBDouble& lhv) const {
    RGBDouble ans(*this);
    ans -= lhv;
    return ans;
}
Bitmap::RGBDouble Bitmap::RGBDouble::operator-(const Bitmap::RGB& lhv) const {
    RGBDouble ans(*this);
    ans -= lhv;
    return ans;
}
Bitmap::RGBDouble Bitmap::RGBDouble::operator*(const double lhv) const {
    RGBDouble ans(*this);
    ans *= lhv;
    return ans;
}
Bitmap::RGBDouble::operator RGB() const {
    unsigned char new_b = static_cast<unsigned char>(b);
    unsigned char new_g = static_cast<unsigned char>(g);
    unsigned char new_r = static_cast<unsigned char>(r);
    if (b > D255) {
        new_b = UC255;
    }
    if (b < D0) {
        new_b = UC0;
    }
    if (g > D255) {
        new_g = UC255;
    }
    if (g < D0) {
        new_g = UC0;
    }
    if (r > D255) {
        new_r = UC255;
    }
    if (r < D0) {
        new_r = UC0;
    }
    return {new_b, new_g, new_r};
}
