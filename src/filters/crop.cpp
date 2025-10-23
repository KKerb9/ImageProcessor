#include "crop.h"
#include <string>

CropFilter::CropFilter() {
    width_ = 0;
    height_ = 0;
}

CropFilter::CropFilter(const int32_t width, const int32_t height) {
    width_ = width;
    height_ = height;
}

CropFilter::CropFilter(const std::vector<std::string>& args) {
    try {
        if (args.size() != 3) {
            throw InvalidCropParams("invalid count\n");
        }
        size_t pos1, pos2;
        width_ = std::stoi(args[1], &pos1);
        height_ = std::stoi(args[2], &pos2);
        if (pos1 != args[1].size() || pos2 != args[2].size()) {
            throw InvalidCropParams(args[1] + " " + args[2]);
        }
    } catch (const InvalidCropParams& e) {
        throw e;
    } catch (const std::exception& e) {
        throw InvalidCropParams(std::string(e.what()) + ": [" + args[1] + " " + args[2] + "]\n");
    }
}

void CropFilter::ApplyFilter(Image& image) {
    if (width_ < 0 || height_ < 0) {
        throw CropException("Size below zero");
    }
    image.end_.first = std::min(image.border_.first, image.start_.first + height_);
    image.end_.second = std::min(image.border_.second, image.start_.second + width_);
}

CropException::CropException(const std::string& msg) {
    msg_ = "Crop: \n\t" + msg;
}

const char* CropException::what() const noexcept {
    return msg_.c_str();
}
