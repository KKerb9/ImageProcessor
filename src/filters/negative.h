#pragma once

#include "filter.h"

class NegativeFilter : public Filter {
public:
    void ApplyFilter(Image& image) override;
};

class NegativeException : public std::exception {
public:
    explicit NegativeException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string msg_;
};

class InvalidNegativeParams : public NegativeException {
public:
    explicit InvalidNegativeParams(const std::string& params)
        : NegativeException("Invalid parameters for Negative: " + params)
    {}
};
