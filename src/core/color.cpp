#include "color.h"
#include <algorithm>

Color::Color() {
    red_ = 0.0;
    green_ = 0.0;
    blue_ = 0.0;
}

Color::Color(const uint8_t red, const uint8_t green, const uint8_t blue) {
    red_ = static_cast<double>(red);
    red_ /= 255.0;
    green_ = static_cast<double>(green);
    green_ /= 255.0;
    blue_ = static_cast<double>(blue);
    blue_ /= 255.0;
}

Color::Color(const uint32_t pixel) {
    uint8_t blue = pixel & ((1 << 8) - 1);
    uint8_t green = (pixel & (((1 << 8) - 1) << 8)) >> 8;
    uint8_t red = (pixel & (((1 << 8) - 1) << 16)) >> 16;
    red_ = static_cast<double>(red);
    red_ /= 255.0;
    green_ = static_cast<double>(green);
    green_ /= 255.0;
    blue_ = static_cast<double>(blue);
    blue_ /= 255.0;
}

Color::Color(const double red, const double green, const double blue) :
    red_(red),
    green_(green),
    blue_(blue)
{}

Color::Color(const double c) :
    red_(c),
    green_(c),
    blue_(c)
{}

std::array<double, 3> Color::GetInfo() const {
    return {red_, green_, blue_};
}

Color operator*(const double x, const Color& y) {
    return Color(y.red_ * x, y.green_ * x, y.blue_ * x);
}

Color Color::operator+(const Color& other) const {
    return Color(red_ + other.red_, green_ + other.green_, blue_ + other.blue_);
}

Color& Color::operator+=(const Color& other) {
    red_ = red_ + other.red_;
    green_ = green_ + other.green_;
    blue_ = blue_ + other.blue_;
    return *this;
}

bool Color::operator>(const double other) const {
    return std::max({red_, green_, blue_}) > other; 
}

Color& Color::Normalize() {
    red_ = std::clamp(red_, min_value, max_value);
    green_ = std::clamp(green_, min_value, max_value);
    blue_ = std::clamp(blue_, min_value, max_value);
    return *this;
}

ColorException::ColorException(const std::string& msg) {
    msg_ = "Color: \n\t" + msg;
}

const char* ColorException::what() const noexcept {
    return msg_.c_str();
}
