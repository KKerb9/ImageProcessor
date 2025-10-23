#include "negative.h"

void NegativeFilter::ApplyFilter(Image& image) {
    try {
        for (int32_t i = image.start_.first; i < image.end_.first; i++) {
            for (int32_t j = image.start_.second; j < image.end_.second; j++) {
                auto [r, g, b] = image.GetPixel(i, j).GetInfo();
                image.SetPixel(i, j, Color(1.0 - r, 1.0 - g, 1.0 - b).Normalize());
            }
        }
    } catch (const std::exception& e) {
        throw NegativeException(std::string("Unexpected Error: \n\t") + e.what());
    }
}

NegativeException::NegativeException(const std::string& msg) {
    msg_ = "Negative: \n\t" + msg;
}

const char* NegativeException::what() const noexcept {
    return msg_.c_str();
}
