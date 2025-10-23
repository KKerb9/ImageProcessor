#include "image.h"

Image::Image() {
    start_ = {0, 0};
    end_ = {0, 0};
    border_ = {0, 0};
}

Image::Image(const int32_t height, const int32_t width) {
    start_ = {0, 0};
    end_ = {height, width};
    border_ = {height, width};
    table_.resize(height, std::vector<Color>(width));
}

Image::Image(const Image& other) {
    table_ = other.table_;
    start_ = other.start_;
    end_ = other.end_;
    border_ = other.border_;
}

int32_t Image::GetWidth() const {
    return end_.second - start_.second;
}

int32_t Image::GetHeight() const {
    return end_.first - start_.first;
}

bool Image::AreValidCoords(const int32_t pos_x, const int32_t pos_y) const noexcept {
    return pos_x >= start_.first && pos_x < end_.first && pos_y >= start_.second && pos_y < end_.second;
}

void Image::SetPixel(const int32_t pos_x, const int32_t pos_y, const uint32_t pixel) {
    if (!AreValidCoords(pos_x, pos_y)) {
        throw ImageException("Invalid coords to set pixel\n");  // TODO сделать что бы выводило координаты и границы
    }
    table_[pos_x][pos_y] = Color(pixel);
}

void Image::SetPixel(const int32_t pos_x, const int32_t pos_y, const Color& pixel) {
    if (!AreValidCoords(pos_x, pos_y)) {
        throw ImageException("Invalid coords to set pixel\n");  // TODO сделать что бы выводило координаты и границы
    }
    table_[pos_x][pos_y] = pixel;
}

Color Image::GetPixel(const int32_t pos_x, const int32_t pos_y) const {
    if (!AreValidCoords(pos_x, pos_y)) {
        throw ImageException("Invalid coords to get pixel\n");  // TODO сделать что бы выводило координаты и границы
    }
    return table_[pos_x][pos_y];
}

Color Image::GetPixelSafe(int32_t pos_x, int32_t pos_y) const noexcept {
    if (border_.first == 0 || border_.second == 0) {
        return Color();
    }
    if (pos_x < start_.first) {
        pos_x = start_.first;
    } else if (pos_x >= end_.first) {
        pos_x = end_.first - 1;
    }
    if (pos_y < start_.second) {
        pos_y = start_.second;
    } else if (pos_y >= end_.second) {
        pos_y = end_.second - 1;
    }
    return table_[pos_x][pos_y];
}

Image& Image::operator=(const Image& other) {
    start_ = other.start_;
    end_ = other.end_;
    border_ = other.border_;
    table_ = other.table_;
    return *this;
}

ImageException::ImageException(const std::string& msg) {
    msg_ = "Image: \n\t" + msg;
}

const char* ImageException::what() const noexcept {
    return msg_.c_str();
}
