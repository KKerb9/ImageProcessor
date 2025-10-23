#pragma once

#include "../core/image.h"
#include <filesystem>

class ReaderException : public std::exception {
public:
    explicit ReaderException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string msg_;
};

Image ReadFromBMPFile(const std::filesystem::path& input_file);
