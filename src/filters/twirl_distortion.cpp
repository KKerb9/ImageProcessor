#include "twirl_distortion.h"

#include <cmath>

TwirlDistortionFilter::TwirlDistortionFilter() :
    center_({0, 0}),
    radius_(0.0),
    angle_(3.14)
{}

TwirlDistortionFilter::TwirlDistortionFilter(
    const std::pair<int32_t, int32_t> center,
    const double radius, 
    const double angle
) :
    center_(center),
    radius_(radius),
    angle_(angle)
{}

TwirlDistortionFilter::TwirlDistortionFilter(const std::vector<std::string>& args) {
    try {
        if (args.size() != 5) {
            throw InvalidTwirlDistortionParams("Invalid count\n");
        }
        size_t pos1, pos2, pos3, pos4;
        center_.first = std::stoi(args[1], &pos1);
        center_.second = std::stoi(args[2], &pos2);
        radius_ = std::stod(args[3], &pos3);
        angle_ = std::stod(args[4], &pos4);
        if (pos1 != args[1].size() || pos2 != args[2].size() || pos3 != args[3].size() || pos4 != args[4].size()) {
            throw InvalidTwirlDistortionParams(args[1] + " " + args[2] + " " + args[3] + " " + args[4]);
        }
    } catch (const InvalidTwirlDistortionParams& e) {
        throw e;
    } catch (const std::exception& e) {
        throw InvalidTwirlDistortionParams(std::string(e.what()) + ": [" + args[1] + " " + args[2] + " " + args[3] + " " + args[4] + "]\n");
    }
}

void TwirlDistortionFilter::ApplyFilter(Image& image) {
    try {
        int32_t h = image.GetHeight();
        int32_t w = image.GetWidth();
        Image new_one(h, w);
        for (int32_t i = image.start_.first; i < image.end_.first; i++) {
            for (int32_t j = image.start_.second; j < image.end_.second; j++) {
                double dx = (i - center_.first);
                double dy = (j - center_.second);
                double dd = dx * dx + dy * dy;
                double rr = radius_ * radius_;
                double dr = sqrt(dd);
                if (dd > rr) {
                    new_one.SetPixel(i - image.start_.first, j - image.start_.second, image.GetPixel(i, j));
                } else {
                    double turn = std::atan2(dy, dx) + angle_ * ((radius_ - dr) / radius_);
                    double nx = center_.first + std::cos(turn) * dr;
                    double ny = center_.second + std::sin(turn) * dr;
                    int32_t nxi = static_cast<int32_t>(std::round(nx));
                    int32_t nyi = static_cast<int32_t>(std::round(ny));
                    new_one.SetPixel(i - image.start_.first, j - image.start_.second, image.GetPixelSafe(nxi, nyi));
                }
            }
        }
        image = new_one;
    } catch (const std::exception& e) {
        throw TwirlDistortionException(e.what());
    }
}

TwirlDistortionException::TwirlDistortionException(const std::string& msg) {
    msg_ = "Twirl Distortion: \n\t" + msg;
}

const char* TwirlDistortionException::what() const noexcept {
    return msg_.c_str();
}
