#include "processor.h"
#include "../io/reader.h"
#include "../io/writer.h"

Processor::Processor(
    const std::filesystem::path& input_file_path,
    const std::filesystem::path& output_file_path,
    std::vector<std::unique_ptr<Filter>>& filters
) :
    input_file_path_(input_file_path),
    output_file_path_(output_file_path),
    filters_(std::move(filters))
{
    try {
        image_ = ReadFromBMPFile(input_file_path);
    } catch (const ReaderException& e) {
        throw ProcessorException(e.what());
    } catch (const std::exception& e) {
        throw ProcessorException(std::string("Unexpected Error: \t") + e.what());
    }
}

void Processor::MakeProcess() {
    // apply filters ==================================================
    try {
        for (const auto& f : filters_) f->ApplyFilter(image_);
    } catch (const std::exception& e) {
        throw ProcessorException(std::string("Unexpected Error: ") + e.what());
    }
    // write final version to the output file =========================
    try {
        WriteToBMPFile(output_file_path_, image_);
    } catch (const WriterException& e) {
        throw ProcessorException(e.what());
    } catch (const std::exception& e) {
        throw ProcessorException(std::string("Unexpected Error: ") + e.what());
    }
}

ProcessorException::ProcessorException(const std::string& msg) {
    msg_ = "Processor: \n\t" + msg;
}

const char* ProcessorException::what() const noexcept {
    return msg_.c_str();
}
