#include "edge_detection.h"
#include <array>
#include "grayscale.h"
#include "sharpening.h"

EdgeDetectionFilter::EdgeDetectionFilter() {
    mask_[0][1] = -1.0;
    mask_[1][0] = -1.0;
    mask_[2][1] = -1.0;
    mask_[1][2] = -1.0;
    mask_[1][1] = 4.0;
    mask_[0][0] = 0.0;
    mask_[2][0] = 0.0;
    mask_[2][2] = 0.0;
    mask_[0][2] = 0.0;
    threshold_ = 0.0;
}

EdgeDetectionFilter::EdgeDetectionFilter(const double threshold) {
    mask_[0][1] = -1.0;
    mask_[1][0] = -1.0;
    mask_[2][1] = -1.0;
    mask_[1][2] = -1.0;
    mask_[1][1] = 4.0;
    mask_[0][0] = 0.0;
    mask_[2][0] = 0.0;
    mask_[2][2] = 0.0;
    mask_[0][2] = 0.0;
    threshold_ = threshold;
}

EdgeDetectionFilter::EdgeDetectionFilter(const std::vector<std::string>& args) {
    try {
        if (args.size() != 2) {
            throw InvalidEdgeDetectionParams("invalid count\n");
        }
        size_t pos;
        threshold_ = std::stod(args[1], &pos);
        if (pos != args[1].size()) {
            throw InvalidEdgeDetectionParams(args[1]);
        }
        mask_[0][1] = -1.0;
        mask_[1][0] = -1.0;
        mask_[2][1] = -1.0;
        mask_[1][2] = -1.0;
        mask_[1][1] = 4.0;
        mask_[0][0] = 0.0;
        mask_[2][0] = 0.0;
        mask_[2][2] = 0.0;
        mask_[0][2] = 0.0;
    } catch (const InvalidEdgeDetectionParams& e) {
        throw e;
    } catch (const std::exception& e) {
        throw InvalidEdgeDetectionParams(std::string(e.what()) + ": [" + args[1] + "]\n");
    }
}

void EdgeDetectionFilter::ApplyFilter(Image& image) {
    try {
        GrayscaleFilter().ApplyFilter(image);
        SharpeningFilter(mask_).ApplyFilter(image);
        for (int32_t i = image.start_.first; i < image.end_.first; i++) {
            for (int32_t j = image.start_.second; j < image.end_.second; j++) {
                image.SetPixel(i, j, Color(image.GetPixel(i, j) > threshold_ ? 1.0 : 0.0));
            }
        }
    } catch (const std::exception& e) {
        throw EdgeDetectionException(e.what());
    }
}

EdgeDetectionException::EdgeDetectionException(const std::string& msg) {
    msg_ = "Edge Detection: \n\t" + msg;
}

const char* EdgeDetectionException::what() const noexcept {
    return msg_.c_str();
}
