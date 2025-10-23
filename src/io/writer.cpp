#include "writer.h"
#include <filesystem>
#include <fstream>
#include <exception>

void WriteToBMPFile(const std::filesystem::path& output_file, Image& image) {
    try {
        const uint32_t BITMAPFILEHEADER_SIZE = 14;
        const uint32_t BITMAPINFOHEADER_SIZE = 40;
        const uint32_t biBitCount = 24;
        const uint32_t biPlanes = 1;
        const uint32_t biCompression = 0;
        const uint32_t biXPelsPerMeter = 2835;
        const uint32_t biClrUsed = 0;
        const uint32_t biClrImportant = 0;
        int32_t width = image.GetWidth();
        int32_t height = image.GetHeight();
        int32_t row_size = ((width * 3) + 3) / 4 * 4;
        uint32_t image_size = row_size * height;
        uint32_t file_size = BITMAPFILEHEADER_SIZE + BITMAPINFOHEADER_SIZE + image_size;
        uint32_t param = 0;
        uint32_t bfOffBits = BITMAPFILEHEADER_SIZE + BITMAPINFOHEADER_SIZE;

        std::ofstream file{output_file, std::ios::binary};
        if (!file) {
            throw std::runtime_error("Invalid file path\n");
        }

        // BITMAPFILEHEADER ==================================================
        file.put('B');
        file.put('M');
        file.write(reinterpret_cast<const char*>(&file_size), 4);
        file.write(reinterpret_cast<const char*>(&param), 4);
        file.write(reinterpret_cast<const char*>(&bfOffBits), 4);
        // BITMAPINFOHEADER ==================================================
        file.write(reinterpret_cast<const char*>(&BITMAPINFOHEADER_SIZE), 4);
        file.write(reinterpret_cast<const char*>(&width), 4);
        file.write(reinterpret_cast<const char*>(&height), 4);
        file.write(reinterpret_cast<const char*>(&biPlanes), 2);
        file.write(reinterpret_cast<const char*>(&biBitCount), 2);
        file.write(reinterpret_cast<const char*>(&biCompression), 4);
        file.write(reinterpret_cast<const char*>(&image_size), 4);
        file.write(reinterpret_cast<const char*>(&biXPelsPerMeter), 4);
        file.write(reinterpret_cast<const char*>(&biXPelsPerMeter), 4);
        file.write(reinterpret_cast<const char*>(&biClrUsed), 4);
        file.write(reinterpret_cast<const char*>(&biClrImportant), 4);
        // PIXEL DATA ========================================================
        for (int32_t i = height - 1; i >= 0; i--) {
            for (int32_t j = 0; j < width; j++) {
                auto [r, g, b] = image.GetPixel(i, j).Normalize().GetInfo();
                uint8_t rB = static_cast<uint8_t>(r * 255.0);
                uint8_t gB = static_cast<uint8_t>(g * 255.0);
                uint8_t bB = static_cast<uint8_t>(b * 255.0);
                file.write(reinterpret_cast<const char*>(&bB), 1);
                file.write(reinterpret_cast<const char*>(&gB), 1);
                file.write(reinterpret_cast<const char*>(&rB), 1);
            }
            if (row_size > width * 3) {
                uint32_t trash = 0;
                file.write(reinterpret_cast<const char*>(&trash), row_size - width * 3);
            }
        }
    } catch (const std::exception& e) {
        throw WriterException(e.what());
    }
}

WriterException::WriterException(const std::string& msg) {
    msg_ = "Writer: \n\t" + msg;
}

const char* WriterException::what() const noexcept {
    return msg_.c_str();
}
