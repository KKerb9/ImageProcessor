#include "filter.h"
#include "crop.h"
#include "grayscale.h"
#include "negative.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "gaussian_blur.h"
#include "twirl_distortion.h"

#include <string>

#include <iostream>

std::unique_ptr<Filter> Filter::IdentifyFilter(const std::vector<std::string>& args) {
    try {
        // фильтров мало, так что решил не морочиться с фабрикой
        if (args[0] == "-crop") {
            return std::make_unique<CropFilter>(args);
        } else if (args[0] == "-gs") {
            return std::make_unique<GrayscaleFilter>();
        } else if (args[0] == "-neg") {
            return std::make_unique<NegativeFilter>();
        } else if (args[0] == "-sharp") {
            return std::make_unique<SharpeningFilter>();
        } else if (args[0] == "-edge") {
            return std::make_unique<EdgeDetectionFilter>(args);
        } else if (args[0] == "-blur") {
            return std::make_unique<GaussianBlurFilter>(args);
        } else if (args[0] == "-twirl") {
            return std::make_unique<TwirlDistortionFilter>(args);
        } else {
            throw UnknownFilter(args[0]);
        }
    } catch (const std::exception& e) {
        throw FilterException(e.what());
    }
}

FilterException::FilterException(const std::string& msg) {
    msg_ = "Filter: \n\t" + msg;
}

const char* FilterException::what() const noexcept {
    return msg_.c_str();
}
