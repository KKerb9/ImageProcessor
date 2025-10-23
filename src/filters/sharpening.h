#pragma once

#include "filter.h"

class SharpeningFilter : public Filter {
public:
    SharpeningFilter();
    explicit SharpeningFilter(double (&mask)[3][3]);
    void ApplyFilter(Image& image) override;
private:
    double mask_[3][3];
};

class SharpeningException : public std::exception {
public:
    explicit SharpeningException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string msg_;
};

class InvalidSharpeningParams : public SharpeningException {
public:
    explicit InvalidSharpeningParams(const std::string& params)
        : SharpeningException("Invalid parameters for Sharpening: " + params)
    {}
};
