#pragma once

#include "color.h"
#include <vector>

class Image {
public:
    Image();
    Image(const int32_t height, const int32_t width);
    Image(const Image& other);
    ~Image() = default;

    Image& operator=(const Image& other);

    int32_t GetWidth() const;
    int32_t GetHeight() const;

    bool AreValidCoords(const int32_t pos_x, const int32_t pos_y) const noexcept;
    
    void SetPixel(const int32_t pos_x, const int32_t pos_y, const uint32_t pixel);
    void SetPixel(const int32_t pos_x, const int32_t pos_y, const Color& pixel);
    Color GetPixel(const int32_t pos_x, const int32_t pos_y) const;
    Color GetPixelSafe(int32_t pos_x, int32_t pos_y) const noexcept;
private:
    /*
        мб надо сделать отдельные ручки для изменений, а не кучу френдов
        не знаю как лучше.
    */
    friend class CropFilter;
    friend class GrayscaleFilter;
    friend class NegativeFilter;
    friend class SharpeningFilter;
    friend class EdgeDetectionFilter;
    friend class GaussianBlurFilter;
    friend class TwirlDistortionFilter;

    std::pair<int32_t, int32_t> start_;  // {x, y}
    std::pair<int32_t, int32_t> end_;  // {x, y}
    std::pair<int32_t, int32_t> border_;  // {x, y}
    std::vector<std::vector<Color>> table_;
};

class ImageException : public std::exception {
public:
    explicit ImageException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string msg_;
};
