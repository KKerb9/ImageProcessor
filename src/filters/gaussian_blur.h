#pragma once

#include "filter.h"

class GaussianBlurFilter : public Filter {
public:
    GaussianBlurFilter();
    explicit GaussianBlurFilter(const double sigma);
    explicit GaussianBlurFilter(const std::vector<std::string>& args);

    void ApplyFilter(Image& image) override;
private:
    double sigma_;
};

class GaussianBlurException : public std::exception {
public:
    explicit GaussianBlurException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string msg_;
};

class InvalidGaussianBlurParams : public GaussianBlurException {
public:
    explicit InvalidGaussianBlurParams(const std::string& params)
        : GaussianBlurException("Invalid parameters for Gaussian Blur: " + params)
    {}
};
