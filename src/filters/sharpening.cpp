#include "sharpening.h"
#include <array>

SharpeningFilter::SharpeningFilter() {
    mask_[0][1] = -1.0;
    mask_[1][0] = -1.0;
    mask_[2][1] = -1.0;
    mask_[1][2] = -1.0;
    mask_[1][1] = 5.0;
    mask_[0][0] = 0.0;
    mask_[2][0] = 0.0;
    mask_[2][2] = 0.0;
    mask_[0][2] = 0.0;
}

SharpeningFilter::SharpeningFilter(double (&mask)[3][3]) {
    try {
        std::copy(mask[0], mask[0] + 3, mask_[0]);
        std::copy(mask[1], mask[1] + 3, mask_[1]);
        std::copy(mask[2], mask[2] + 3, mask_[2]);
    } catch (const std::exception& e) {
        throw SharpeningException(e.what());
    }
}

void SharpeningFilter::ApplyFilter(Image& image) {
    try {
        int32_t h = image.GetHeight();
        int32_t w = image.GetWidth();
        Image new_one(h, w);
        for (int32_t i = image.start_.first; i < image.end_.first; i++) {
            for (int32_t j = image.start_.second; j < image.end_.second; j++) {
                Color left = image.GetPixelSafe(i, j - 1);
                Color right = image.GetPixelSafe(i, j + 1);
                Color up = image.GetPixelSafe(i - 1, j);
                Color down = image.GetPixelSafe(i + 1, j);
                Color center = image.GetPixelSafe(i, j);
                Color cur = mask_[1][0] * left +
                            mask_[1][2] * right +
                            mask_[0][1] * up +
                            mask_[2][1] * down +
                            mask_[1][1] * center;
                new_one.SetPixel(i - image.start_.first, j - image.start_.second, cur.Normalize());
            }
        }
        image = new_one;
    } catch (const std::exception& e) {
        throw SharpeningException(std::string("Unexpected Error: \n\t") + e.what());
    }
}

SharpeningException::SharpeningException(const std::string& msg) {
    msg_ = "Sharpening: \n\t" + msg;
}

const char* SharpeningException::what() const noexcept {
    return msg_.c_str();
}
