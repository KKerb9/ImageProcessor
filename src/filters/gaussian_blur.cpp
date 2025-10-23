// #pragma GCC optimize("O3,unroll-loops")  эххх clang -rep

#include "gaussian_blur.h"
#include <cmath>

GaussianBlurFilter::GaussianBlurFilter() :
    sigma_(0.0)
{}

GaussianBlurFilter::GaussianBlurFilter(const double sigma) :
    sigma_(sigma)
{}

GaussianBlurFilter::GaussianBlurFilter(const std::vector<std::string>& args) {
    try {
        if (args.size() != 2) {
            throw InvalidGaussianBlurParams("invalid count\n");
        }
        size_t pos;
        sigma_ = std::stod(args[1], &pos);
        if (pos != args[1].size()) {
            throw InvalidGaussianBlurParams(args[1]);
        }
    } catch (const InvalidGaussianBlurParams& e) {
        throw e;
    } catch (const std::exception& e) {
        throw InvalidGaussianBlurParams(std::string(e.what()) + ": [" + args[1] + "]\n");
    }
}

void GaussianBlurFilter::ApplyFilter(Image& image) {
    try {
        const double znm = sigma_ * sigma_ * 2.0;
        const int32_t K = 3 * static_cast<int32_t>(std::ceil(sigma_));
        int32_t h = image.GetHeight();
        int32_t w = image.GetWidth();
        Image new_one(h, w);
        std::vector<std::vector<Color>> res(h, std::vector<Color>(w));
        std::vector<std::vector<Color>> res2(h, std::vector<Color>(w));
        std::vector<double> kernel(K * 2 + 1);
        double summ = 0.0;
        for (int32_t i = 0; i <= K * 2; i++) {
            kernel[i] = exp(-((i - K) * (i - K)) / znm);
            summ += kernel[i];
        }
        for (int32_t i = 0; i <= K * 2; i++) {
            kernel[i] /= summ;
        }
        for (int32_t i = 0; i < h; i++) {
            for (int32_t j = 0; j < w; j++) {
                for (int32_t k = -K; k <= K; k++) {
                    res[i][j] += kernel[k + K] * image.GetPixelSafe(image.start_.first + k + i, image.start_.second + j);
                }
            }
        }
        for (int32_t j = 0; j < w; j++) {
            for (int32_t i = 0; i < h; i++) {
                for (int32_t k = -K; k <= K; k++) {
                    res2[i][j] += kernel[k + K] * res[i][std::max(0, std::min(w - 1, j + k))];
                }
            }
        }
        for (int32_t i = 0; i < h; i++) {
            for (int32_t j = 0; j < w; j++) {
                new_one.SetPixel(i, j, res2[i][j]);
            }
        }
        image = new_one;
    } catch (const std::exception& e) {
        throw GaussianBlurException(std::string("Unexpected Error: \n\t") + e.what());
    }
}

GaussianBlurException::GaussianBlurException(const std::string& msg) {
    msg_ = "Gaussian Blur: \n\t" + msg;
}

const char* GaussianBlurException::what() const noexcept {
    return msg_.c_str();
}
