# Project Task List

Status legend: [x] done, [~] in progress, [ ] todo

## CImg → Qt6/OpenCV migration
- [x] Replace upstream CImg dependency with a local compatibility shim (`src/CImg.h`) that mimics only required APIs
- [~] Build the project against Qt6 and OpenCV on Linux (install `qt6-base-dev`, `qt6-5compat-dev`, `libopencv-dev`)
- [ ] Remove remaining CImg idioms by migrating core image code to `cv::Mat`/`QImage` primitives
- [ ] Replace `CImg_to_QImage` with direct, zero-copy paths where possible
- [ ] Replace `draw_axis`/colorbar with Qt painting (labels/ticks) and remove shim no-op
- [ ] Validate registration pipeline (control points, affine) against OpenCV-only implementation

## Image processing and performance
- [ ] Optimize naive `convolve`, `blur`, and resize in shim or move to OpenCV equivalents
- [ ] Add unit/perf tests for SC computation paths (8-bit, 16-bit, temporal)

## Build, packaging, CI
- [x] Add CI workflow (Linux) to build and run basic tests
- [x] Document Linux dependencies and CMake presets
- [ ] Optional: Windows build with Qt6 and OpenCV via vcpkg

## UI/UX
- [x] Replace About dialog CImg version with shim label or remove
- [ ] Add option to toggle OpenCV/Qt backends if both are present

## Camera and video
- [ ] Verify USB/video-in with OpenCV capture devices (exposure, FPS)
- [ ] Validate Basler/Pylon path after image changes
- [ ] Install Basler Pylon SDK and rebuild with `SPECKLE_USE_PYLON=ON` to confirm hardware integration (currently blocked by network restrictions)

## Documentation
- [x] Add TASKS.md
- [x] Add LESSONS_LEARNED.md
- [x] Update README to reflect Qt6/Linux support and migration status
