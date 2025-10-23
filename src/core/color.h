#pragma once

#include <cstdint>
#include <string>
#include <array>
#include <algorithm>

class Color {
public:
    Color();
    Color(const uint8_t red, const uint8_t green, const uint8_t blue);
    explicit Color(const uint32_t pixel);
    Color(double red, double green, double blue);
    explicit Color(double c);

    std::array<double, 3> GetInfo() const;
    Color& Normalize();

    friend Color operator*(const double x, const Color& y);
    Color operator+(const Color& other) const;
    Color& operator+=(const Color& other);
    bool operator>(const double other) const;
private:
    friend class Image;

    double red_;
    double green_;
    double blue_;
public:
    static constexpr double min_value = 0.0;
    static constexpr double max_value = 1.0;
};

Color operator*(const double x, const Color& y);

class ColorException : public std::exception {
public:
    explicit ColorException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string msg_;
};
