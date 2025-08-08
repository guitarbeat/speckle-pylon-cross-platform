#pragma once

// Minimal compatibility shim for parts of CImg used in this project.
// Backed by a simple planar buffer and light-weight operations.
// This is NOT a full CImg implementation.

#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <cstdint>

#ifdef SPECKLE_USE_OPENCV
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#endif

namespace cimg_library {

static const char* cimg_version = "compat-0.1";

// Loop macros used in codebase
#define cimg_forX(img, x) for (int x = 0; x < (img).width(); ++x)
#define cimg_forXY(img, x, y) for (int y = 0; y < (img).height(); ++y) for (int x = 0; x < (img).width(); ++x)
#define cimg_forXYZ(img, x, y, z) for (int z = 0; z < (img).depth(); ++z) for (int y = 0; y < (img).height(); ++y) for (int x = 0; x < (img).width(); ++x)
#define cimg_for_inXY(img, xmin, ymin, xmax, ymax, x, y) for (int y = (ymin); y <= (ymax); ++y) for (int x = (xmin); x <= (xmax); ++x)

// Simple planar image container: data layout [c][z][y][x] contiguous per plane
// Only subset of API required by project is implemented.

template <typename T>
class CImg {
public:
    CImg() : w_(0), h_(0), d_(0), c_(0) {}
    CImg(int w, int h, int d = 1, int c = 1, T fillValue = T()) { resize(w, h, d, c, fillValue); }

    // Width/height/depth/channels
    int width() const { return w_; }
    int height() const { return h_; }
    int depth() const { return d_; }
    int spectrum() const { return c_; }

    bool is_empty() const { return buf_.empty() || w_ <= 0 || h_ <= 0 || d_ <= 0 || c_ <= 0; }

    // Element access (planar storage). No bounds checks for performance.
    T& operator()(int x, int y) { return at(x, y, 0, 0); }
    const T& operator()(int x, int y) const { return at_const(x, y, 0, 0); }
    T& operator()(int x, int y, int z) { return at(x, y, z, 0); }
    const T& operator()(int x, int y, int z) const { return at_const(x, y, z, 0); }
    T& operator()(int x, int y, int z, int c) { return at(x, y, z, c); }
    const T& operator()(int x, int y, int z, int c) const { return at_const(x, y, z, c); }

    // 1D accessor for vector-like images
    T& operator()(int i) { return buf_[i]; }
    const T& operator()(int i) const { return buf_[i]; }

    // Raw pointers
    T* data() { return buf_.empty() ? nullptr : buf_.data(); }
    const T* data() const { return buf_.empty() ? nullptr : buf_.data(); }

    // Pointer to pixel plane
    T* data(int x, int y, int z = 0, int c = 0) {
        return buf_.data() + offset(x, y, z, c);
    }
    const T* data(int x, int y, int z = 0, int c = 0) const {
        return buf_.data() + offset(x, y, z, c);
    }

    // Size/resize (in-place). Returns reference for chaining like original CImg
    CImg<T>& resize(int w, int h, int d = 1, int c = 1, T fillValue = T()) {
        w_ = w; h_ = h; d_ = d; c_ = c;
        buf_.assign(size(), fillValue);
        return *this;
    }

    // In-place resize to match reference image (nearest-neighbor)
    CImg<T>& resize(const CImg<T>& ref, int /*interp*/ = -1) {
        if (w_ == ref.w_ && h_ == ref.h_ && d_ == ref.d_ && c_ == ref.c_) return *this;
        CImg<T> out(ref.w_, ref.h_, ref.d_, std::max(1, c_));
        for (int cc = 0; cc < out.c_; ++cc) {
            for (int zz = 0; zz < out.d_; ++zz) {
                for (int y = 0; y < out.h_; ++y) {
                    int sy = (h_ > 1) ? (y * (h_ - 1) / std::max(1, out.h_ - 1)) : 0;
                    for (int x = 0; x < out.w_; ++x) {
                        int sx = (w_ > 1) ? (x * (w_ - 1) / std::max(1, out.w_ - 1)) : 0;
                        out(x, y, zz, cc) = get_clamped(sx, sy, std::min(zz, d_ - 1), std::min(cc, c_ - 1));
                    }
                }
            }
        }
        *this = std::move(out);
        return *this;
    }

    // Assign from raw pointer (copy into buffer)
    void assign(const T* ptr, int w, int h, int d = 1, int c = 1) {
        w_ = w; h_ = h; d_ = d; c_ = c;
        buf_.assign(ptr, ptr + size());
    }

    // Fill
    void fill(T v) { std::fill(buf_.begin(), buf_.end(), v); }

    // Fill specific pixel with color components (used to zero RGB)
    void fillC(int x, int y, T r, T g, T b, T /*a*/ = T()) {
        if (c_ < 3) return;
        (*this)(x, y, 0, 0) = r;
        (*this)(x, y, 0, 1) = g;
        (*this)(x, y, 0, 2) = b;
    }

    // Transpose (swap x/y)
    void transpose() {
        CImg<T> out(h_, w_, d_, c_);
        for (int cc = 0; cc < c_; ++cc)
            for (int zz = 0; zz < d_; ++zz)
                for (int y = 0; y < h_; ++y)
                    for (int x = 0; x < w_; ++x)
                        out(y, x, zz, cc) = (*this)(x, y, zz, cc);
        *this = std::move(out);
    }

    // Mirror along axis: 'x' vertical flip, 'y' horizontal flip
    void mirror(char axis) {
        if (axis == 'x') { // vertical flip
            for (int cc = 0; cc < c_; ++cc)
                for (int zz = 0; zz < d_; ++zz)
                    for (int y = 0; y < h_ / 2; ++y)
                        for (int x = 0; x < w_; ++x)
                            std::swap((*this)(x, y, zz, cc), (*this)(x, h_ - 1 - y, zz, cc));
        } else if (axis == 'y') { // horizontal flip
            for (int cc = 0; cc < c_; ++cc)
                for (int zz = 0; zz < d_; ++zz)
                    for (int y = 0; y < h_; ++y)
                        for (int x = 0; x < w_ / 2; ++x)
                            std::swap((*this)(x, y, zz, cc), (*this)(w_ - 1 - x, y, zz, cc));
        }
    }

    // Rotate by multiples of 90 degrees; round angle to nearest multiple of 90
    void rotate(float degrees) {
        int k = static_cast<int>(std::round(degrees / 90.0f)) % 4;
        if (k < 0) k += 4;
        for (int i = 0; i < k; ++i) rotate90();
    }

    // Permute axes: support only pattern "yxzc" used by project
    void permute_axes(const char* order) {
        if (std::strcmp(order, "yxzc") == 0) {
            // x'=y, y'=x, z'=z, c'=c
            CImg<T> out(h_, w_, d_, c_);
            for (int cc = 0; cc < c_; ++cc)
                for (int zz = 0; zz < d_; ++zz)
                    for (int y = 0; y < h_; ++y)
                        for (int x = 0; x < w_; ++x)
                            out(y, x, zz, cc) = (*this)(x, y, zz, cc);
            *this = std::move(out);
        }
    }

    // Paste image at (x0,y0)
    void draw_image(int x0, int y0, const CImg<T>& img) {
        for (int cc = 0; cc < std::min(c_, img.c_); ++cc)
            for (int y = 0; y < img.h_; ++y) {
                int yy = y0 + y; if (yy < 0 || yy >= h_) continue;
                for (int x = 0; x < img.w_; ++x) {
                    int xx = x0 + x; if (xx < 0 || xx >= w_) continue;
                    (*this)(xx, yy, 0, cc) = img(x, y, 0, cc);
                }
            }
    }

    // Crop ROI [x1,y1]..[x2,y2] inclusive; depth/channels preserved
    CImg<T> get_crop(int x1, int y1, int z1, int x2, int y2, int z2) const {
        int nx = std::max(0, x2 - x1 + 1);
        int ny = std::max(0, y2 - y1 + 1);
        int nz = std::max(0, z2 - z1 + 1);
        CImg<T> out(nx, ny, nz, c_);
        for (int cc = 0; cc < c_; ++cc)
            for (int zz = 0; zz < nz; ++zz)
                for (int y = 0; y < ny; ++y)
                    for (int x = 0; x < nx; ++x)
                        out(x, y, zz, cc) = get_clamped(x1 + x, y1 + y, z1 + zz, cc);
        return out;
    }

    // In-place crop to rectangle (z preserved)
    void crop(int x1, int y1, int x2, int y2) {
        *this = get_crop(x1, y1, 0, x2, y2, std::max(0, d_ - 1));
    }

    // Blur: simple box blur with width ~ sigma
    void blur(int width) {
        if (width <= 1) return;
        // separable box filter horizontal then vertical on each channel
        CImg<T> tmp(w_, h_, d_, c_);
        int r = std::max(1, width / 2);
        for (int cc = 0; cc < c_; ++cc)
            for (int zz = 0; zz < d_; ++zz) {
                // horizontal
                for (int y = 0; y < h_; ++y) {
                    for (int x = 0; x < w_; ++x) {
                        int x1 = std::max(0, x - r), x2 = std::min(w_ - 1, x + r);
                        double sum = 0.0; int cnt = 0;
                        for (int xx = x1; xx <= x2; ++xx) { sum += (*this)(xx, y, zz, cc); ++cnt; }
                        tmp(x, y, zz, cc) = static_cast<T>(sum / std::max(1, cnt));
                    }
                }
                // vertical
                for (int y = 0; y < h_; ++y) {
                    for (int x = 0; x < w_; ++x) {
                        int y1 = std::max(0, y - r), y2 = std::min(h_ - 1, y + r);
                        double sum = 0.0; int cnt = 0;
                        for (int yy = y1; yy <= y2; ++yy) { sum += tmp(x, yy, zz, cc); ++cnt; }
                        (*this)(x, y, zz, cc) = static_cast<T>(sum / std::max(1, cnt));
                    }
                }
            }
    }

    // Square each element in-place (used on floats)
    void sqr() {
        for (auto& v : buf_) v = static_cast<T>(v * v);
    }

    // Naive convolution with float mask (no border handling beyond clamping)
    template <typename M>
    void convolve(const CImg<M>& mask, int /*boundary*/ = 0) {
        assert(mask.c_ == 1 && mask.d_ == 1);
        int mw = mask.w_, mh = mask.h_;
        int rx = mw / 2, ry = mh / 2;
        CImg<T> out(w_, h_, d_, c_);
        for (int cc = 0; cc < c_; ++cc)
            for (int zz = 0; zz < d_; ++zz)
                for (int y = 0; y < h_; ++y)
                    for (int x = 0; x < w_; ++x) {
                        double acc = 0.0;
                        for (int j = 0; j < mh; ++j)
                            for (int i = 0; i < mw; ++i) {
                                int xx = std::clamp(x + i - rx, 0, w_ - 1);
                                int yy = std::clamp(y + j - ry, 0, h_ - 1);
                                acc += (*this)(xx, yy, zz, cc) * mask(i, j);
                            }
                        out(x, y, zz, cc) = static_cast<T>(acc);
                    }
        *this = std::move(out);
    }

    // Statistics: return vector [min, max, mean, variance]
    CImg<double> get_stats() const {
        double mn = std::numeric_limits<double>::infinity();
        double mx = -std::numeric_limits<double>::infinity();
        double sum = 0.0, sum2 = 0.0; size_t n = 0;
        for (const auto& v : buf_) {
            double dv = static_cast<double>(v);
            mn = std::min(mn, dv); mx = std::max(mx, dv);
            sum += dv; sum2 += dv * dv; ++n;
        }
        double mean = (n ? sum / n : 0.0);
        double var = (n ? sum2 / n - mean * mean : 0.0);
        CImg<double> out(4, 1, 1, 1);
        out(0) = mn; out(1) = mx; out(2) = mean; out(3) = var;
        return out;
    }

    // Histogram (returns bins-length float vector) for 1-channel images
    CImg<float> get_histogram(int bins, double minv, double maxv) const {
        CImg<float> hist(bins, 1, 1, 1, 0.0f);
        if (bins <= 0 || maxv <= minv) return hist;
        double scale = (bins - 1) / (maxv - minv);
        for (int zz = 0; zz < std::max(1, d_); ++zz)
            for (int y = 0; y < h_; ++y)
                for (int x = 0; x < w_; ++x) {
                    double v = static_cast<double>((*this)(x, y, zz, 0));
                    int b = static_cast<int>(std::round((v - minv) * scale));
                    if (b >= 0 && b < bins) hist(b) += 1.0f;
                }
        return hist;
    }

    // Extract single channel
    CImg<T> get_channel(int ch) const {
        ch = std::clamp(ch, 0, c_ - 1);
        CImg<T> out(w_, h_, d_, 1);
        for (int zz = 0; zz < d_; ++zz)
            for (int y = 0; y < h_; ++y)
                for (int x = 0; x < w_; ++x)
                    out(x, y, zz, 0) = (*this)(x, y, zz, ch);
        return out;
    }

    // Colormap mapping: current image must be 1-channel 2D; result becomes 3-channel RGB
    void map(const CImg<uint8_t>& colormap) {
        assert(c_ == 1);
        CImg<T> out(w_, h_, d_, 3);
        for (int y = 0; y < h_; ++y)
            for (int x = 0; x < w_; ++x) {
                int idx = std::clamp(static_cast<int>((*this)(x, y)), 0, 255);
                out(x, y, 0, 0) = colormap(idx, 0);
                out(x, y, 0, 1) = colormap(idx, 1);
                out(x, y, 0, 2) = colormap(idx, 2);
            }
        *this = std::move(out);
    }

    // No-op placeholder used in one place; keep for compatibility
    void draw_axis(int /*axis*/, const CImg<float>& /*labels*/, const unsigned char /*black*/[3]) {}

    // Static helper to create vector image from values
    static CImg<T> vector(T a, T b) {
        CImg<T> out(2, 1, 1, 1);
        out(0) = a; out(1) = b;
        return out;
    }

#ifdef SPECKLE_USE_OPENCV
    // Convert to OpenCV Mat (BGR interleaved, 8U3)
    cv::Mat _cimg2cvmat() const {
        if (w_ == 0 || h_ == 0) return cv::Mat();
        cv::Mat m(h_, w_, CV_8UC3);
        for (int y = 0; y < h_; ++y) {
            cv::Vec3b* row = m.ptr<cv::Vec3b>(y);
            for (int x = 0; x < w_; ++x) {
                uint8_t r = static_cast<uint8_t>((*this)(x, y, 0, 0));
                uint8_t g = static_cast<uint8_t>((*this)(x, y, 0, 1));
                uint8_t b = static_cast<uint8_t>((*this)(x, y, 0, 2));
                row[x] = cv::Vec3b(b, g, r);
            }
        }
        return m;
    }

    // Convert from OpenCV Mat (expects BGR interleaved 8U3)
    static CImg<uint8_t> _cvmat2cimg(const cv::Mat& m) {
        assert(m.type() == CV_8UC3);
        CImg<uint8_t> out(m.cols, m.rows, 1, 3, 0);
        for (int y = 0; y < m.rows; ++y) {
            const cv::Vec3b* row = m.ptr<cv::Vec3b>(y);
            for (int x = 0; x < m.cols; ++x) {
                uint8_t b = row[x][0], g = row[x][1], r = row[x][2];
                out(x, y, 0, 0) = r;
                out(x, y, 0, 1) = g;
                out(x, y, 0, 2) = b;
            }
        }
        return out;
    }
#endif

private:
    int w_, h_, d_, c_;
    std::vector<T> buf_;

    size_t size() const { return static_cast<size_t>(w_) * h_ * std::max(1, d_) * std::max(1, c_); }

    size_t plane_stride() const { return static_cast<size_t>(w_) * h_; }
    size_t depth_stride() const { return plane_stride(); }
    size_t channel_stride() const { return plane_stride() * std::max(1, d_); }

    size_t offset(int x, int y, int z, int c) const {
        return static_cast<size_t>(c) * channel_stride() + static_cast<size_t>(z) * depth_stride() + static_cast<size_t>(y) * w_ + x;
    }

    T& at(int x, int y, int z, int c) { return buf_[offset(x, y, z, c)]; }
    const T& at_const(int x, int y, int z, int c) const { return buf_[offset(x, y, z, c)]; }

    T get_clamped(int x, int y, int z, int c) const {
        x = std::clamp(x, 0, std::max(0, w_ - 1));
        y = std::clamp(y, 0, std::max(0, h_ - 1));
        z = std::clamp(z, 0, std::max(0, d_ - 1));
        c = std::clamp(c, 0, std::max(0, c_ - 1));
        return (*this)(x, y, z, c);
    }

    void rotate90() {
        CImg<T> out(h_, w_, d_, c_);
        for (int cc = 0; cc < c_; ++cc)
            for (int zz = 0; zz < d_; ++zz)
                for (int y = 0; y < h_; ++y)
                    for (int x = 0; x < w_; ++x)
                        out(h_ - 1 - y, x, zz, cc) = (*this)(x, y, zz, cc);
        *this = std::move(out);
    }
};

// Very small list wrapper for images

template <typename T>
class CImgList {
public:
    CImgList() = default;

    size_t size() const { return images_.size(); }
    void clear() { images_.clear(); }

    // Remove count images starting from index pos (bounds clamped)
    void remove(size_t pos, size_t count) {
        if (pos >= images_.size()) return;
        size_t end = std::min(images_.size(), pos + count);
        images_.erase(images_.begin() + pos, images_.begin() + end);
    }

    // Assign count images of given size
    void assign(size_t count, int w, int h, int d = 1, int c = 1) {
        images_.clear();
        images_.resize(count);
        for (auto& im : images_) im.resize(w, h, d, c);
    }

    // Insert n default-constructed images at end
    void insert(size_t n) { images_.insert(images_.end(), n, CImg<T>()); }

    // Ensure list has at least index+1 items; ignore count
    void insert(size_t index, size_t /*count*/) {
        if (images_.size() <= index) images_.resize(index + 1);
    }

    CImg<T>& operator[](size_t i) { return images_[i]; }
    const CImg<T>& operator[](size_t i) const { return images_[i]; }

    CImg<T>& at(size_t i) { return images_.at(i); }
    const CImg<T>& at(size_t i) const { return images_.at(i); }

    // Function-call style accessor used by code: ensures size and returns ref
    CImg<T>& operator()(size_t i) {
        if (images_.size() <= i) images_.resize(i + 1);
        return images_[i];
    }

private:
    std::vector<CImg<T>> images_;
};

} // namespace cimg_library