#pragma once

#include "filter.h"

class TwirlDistortionFilter : public Filter {
public:
    TwirlDistortionFilter();
    TwirlDistortionFilter(const std::pair<int32_t, int32_t> center, const double radius, const double angle);
    explicit TwirlDistortionFilter(const std::vector<std::string>& args);
    
    void ApplyFilter(Image& image) override;
private:
    std::pair<int32_t, int32_t> center_;
    double radius_;
    double angle_;
};

class TwirlDistortionException : public std::exception {
public:
    explicit TwirlDistortionException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string msg_;
};

class InvalidTwirlDistortionParams : public TwirlDistortionException {
public:
    explicit InvalidTwirlDistortionParams(const std::string& params)
        : TwirlDistortionException("Invalid parameters for Twirl Distortion: " + params)
    
    {}
};
