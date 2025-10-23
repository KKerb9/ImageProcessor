#pragma once

#include "filter.h"

class CropFilter : public Filter {
public:
    CropFilter();
    CropFilter(const int32_t width, const int32_t height);
    explicit CropFilter(const std::vector<std::string>& args);

    void ApplyFilter(Image& image) override;
private:
    int32_t width_;
    int32_t height_;
};

class CropException : public std::exception {
public:
    explicit CropException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string msg_;
};

class InvalidCropParams : public CropException {
public:
    explicit InvalidCropParams(const std::string& params)
        : CropException("Invalid parameters for Crop: " + params)
    {}
};
