#pragma once

#include "filter.h"

class GrayscaleFilter : public Filter {
public:
    GrayscaleFilter();
    GrayscaleFilter(const double x, const double y, const double z);

    void ApplyFilter(Image& image) override;
private:
    double x_;
    double y_;
    double z_;
};

class GrayscaleException : public std::exception {
public:
    explicit GrayscaleException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string msg_;
};

class InvalidGrayScaleParams : public GrayscaleException {
public:
    explicit InvalidGrayScaleParams(const std::string& params)
        : GrayscaleException("Invalid parameters for Gray Scale: " + params)
    {}
};
