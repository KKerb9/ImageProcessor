#pragma once

#include "filter.h"

class EdgeDetectionFilter : public Filter {
public:
    EdgeDetectionFilter();
    explicit EdgeDetectionFilter(const double threshold);
    explicit EdgeDetectionFilter(const std::vector<std::string>& args);
    void ApplyFilter(Image& image) override;
private:
    double threshold_;
    double mask_[3][3];
};

class EdgeDetectionException : public std::exception {
public:
    explicit EdgeDetectionException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string msg_;
};

class InvalidEdgeDetectionParams : public EdgeDetectionException {
public:
    explicit InvalidEdgeDetectionParams(const std::string& params)
        : EdgeDetectionException("Invalid parameters for Edge Detecrion: " + params)
    {}
};
