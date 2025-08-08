# Lessons Learned: CImg → Qt6/OpenCV Migration

## Why a compatibility shim first
- Incremental replacement avoids a risky big-bang refactor. Implementing only the CImg features used by this codebase enabled a quick compile-time transition.
- The shim keeps public types (`CImg<T>`, `CImgList<T>`, `cimg_for*` macros) stable while enabling Qt6/OpenCV builds.

## API surface required
- Minimal subset covered most needs: planar storage, resize, transpose, mirror, rotate(90° multiples), `permute_axes("yxzc"/"yzcx")`, `convolve`, `blur`, `crop`, `draw_image`, `get_histogram`, `get_channel`, `map(colormap)`, `vector()`.
- Histogram and stats were reimplemented simply; enough for UI, but not optimized.

## Data layout matters
- The app assumes planar R/G/B planes. The shim preserved planar layout so `CImg_to_QImage` (which copies R, G, B planes) continues to work.
- OpenCV interop requires interleaved BGR. Provided `_cimg2cvmat()` and `_cvmat2cimg()` conversions to bridge.

## Display and colorbars
- `draw_axis` for colorbar labels is a no-op in the shim. The eventual fix should render labels using Qt (`QPainter`) and eliminate this dependency.

## Performance considerations
- The shim’s `convolve`/`blur`/resize are naive. For production performance, prefer OpenCV (`cv::filter2D`, `cv::GaussianBlur`, `cv::resize`) and gradually migrate hot paths away from shim calls.

## Build environment
- Linux requires Qt6 and OpenCV development packages. Ensure `qt6-base-dev`, `qt6-5compat-dev`, and `libopencv-dev` are installed before configuring with CMake.
- If root privileges aren’t available in CI/containers, pre-bake dependencies or use a container image with Qt6/OpenCV.

## Migration strategy going forward
- Replace conversion helpers (`CImg_to_QImage`, `_cimg2cvmat`) with direct `QImage`/`cv::Mat` code paths to reduce copies.
- Port SC computation kernels from CImg iteration to OpenCV operations where possible (or keep explicit loops on raw buffers for clarity/perf).
- Remove the shim once no CImg identifiers remain, simplifying maintenance and reducing confusion.

## Testing
- Validate parity on: live view histogram, SC map ranges, overlay alpha blending, registration (control points → affine → pixel mapping).
- Add basic performance checks to avoid regressions during refactors.