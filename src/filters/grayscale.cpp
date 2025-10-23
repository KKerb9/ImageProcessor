#include "grayscale.h"
#include <array>

GrayscaleFilter::GrayscaleFilter() :
    x_(0.299),
    y_(0.587),
    z_(0.114)
{}

GrayscaleFilter::GrayscaleFilter(const double x, const double y, const double z) :
    x_(x),
    y_(y),
    z_(z)
{}

void GrayscaleFilter::ApplyFilter(Image& image) {
    try {
        for (int32_t i = image.start_.first; i < image.end_.first; i++) {
            for (int32_t j = image.start_.second; j < image.end_.second; j++) {
                auto [r, g, b] = image.GetPixel(i, j).GetInfo();
                image.SetPixel(i, j, Color(r * x_ + g * y_ + b * z_).Normalize());
            }
        }
    } catch (const std::exception& e) {
        throw GrayscaleException(std::string("Unexpected Error: \n\t") + e.what());
    }
}

GrayscaleException::GrayscaleException(const std::string& msg) {
    msg_ = "Grayscale: \n\t" + msg;
}

const char* GrayscaleException::what() const noexcept {
    return msg_.c_str();
}
