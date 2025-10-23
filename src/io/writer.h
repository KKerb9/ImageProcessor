#pragma once

#include <filesystem>
#include "../core/image.h"

class WriterException : public std::exception {
public:
    explicit WriterException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string msg_;
};

void WriteToBMPFile(const std::filesystem::path& output_file, Image& img);
