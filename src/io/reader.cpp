#include "reader.h"
#include <fstream>
#include <exception>

Image ReadFromBMPFile(const std::filesystem::path& input_file) {
try {
    const uint16_t bfTypeSize = 2;
    const uint16_t biWidthSize = 4;
    const uint16_t biHeightSize = 4;
    const uint16_t biSizeSize = 4;
    const uint16_t bfOffBitsSize = 4;
    const uint16_t BM = 0x4D42;
    const uint16_t PIXEL_SIZE = 3, TRASH_SIZE = 10;

    std::ifstream file{input_file, std::ios::binary};
    if (!file) {
        throw std::runtime_error("Invalid file path\n");
    }
    uint16_t bfType;
    file.read(reinterpret_cast<char*>(&bfType), bfTypeSize);
    if (bfType != BM) {
        throw std::runtime_error("Invalid file format\n");
    }
    file.seekg(TRASH_SIZE, std::ios::beg);
    uint32_t bfOffBits;
    file.read(reinterpret_cast<char*>(&bfOffBits), bfOffBitsSize);
    file.seekg(biSizeSize, std::ios::cur);
    int32_t width, height;
    file.read(reinterpret_cast<char*>(&width), biWidthSize);
    file.read(reinterpret_cast<char*>(&height), biHeightSize);
    Image image(height, width);
    file.seekg(bfOffBits, std::ios::beg);
    for (int32_t i = 0; i < height; i++) {
        for (int32_t j = 0; j < width; j++) {
            uint32_t cur;
            file.read(reinterpret_cast<char*>(&cur), PIXEL_SIZE);
            image.SetPixel(height - i - 1, j, cur);
        }
        uint32_t ost = (width * 3 + 3) / 4 * 4 - width * 3;
        uint32_t trash;
        file.read(reinterpret_cast<char*>(&trash), ost);
    }
    return image;
} catch (const std::exception& e) {
    throw ReaderException(e.what());
}
}

ReaderException::ReaderException(const std::string& msg) {
    msg_ = "Reader: \n\t" + msg;
}

const char* ReaderException::what() const noexcept {
    return msg_.c_str();
}