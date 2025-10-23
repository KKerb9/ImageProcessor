#pragma once

#include <filesystem>
#include "../filters/filter.h"

class Processor {
public:
    Processor(
        const std::filesystem::path& input_file_path,
        const std::filesystem::path& output_file_path,
        std::vector<std::unique_ptr<Filter>>& filters
    );

    void MakeProcess();
private:
    std::filesystem::path input_file_path_;
    std::filesystem::path output_file_path_;
    Image image_;
    std::vector<std::unique_ptr<Filter>> filters_;
};

class ProcessorException : public std::exception {
public:
    explicit ProcessorException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string msg_;
};
