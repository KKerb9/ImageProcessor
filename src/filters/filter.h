#pragma once
#include "../core/image.h"
#include <memory>  // ругается на unique_ptr
#include <unordered_map>
#include <functional>

class Filter {
public:
    virtual ~Filter() = default;

    static std::unique_ptr<Filter> IdentifyFilter(const std::vector<std::string>& args);
    virtual void ApplyFilter(Image& image) = 0;  // virtual + override что бы работал vptr
};

class FilterException : public std::exception {
public:
    explicit FilterException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string msg_;
};

class UnknownFilter : public FilterException {
public:
    explicit UnknownFilter(const std::string& filter_name)
        : FilterException("No Filter with this name: " + filter_name)
    {}
};
