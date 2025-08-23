# Remaining Task List

## CImg → Qt6/OpenCV migration
- [ ] Remove remaining CImg idioms by migrating core image code to `cv::Mat`/`QImage` primitives
- [ ] Replace `CImg_to_QImage` with direct, zero-copy paths where possible
- [ ] Replace `draw_axis`/colorbar with Qt painting (labels/ticks) and remove shim no-op
- [ ] Validate registration pipeline (control points, affine) against OpenCV-only implementation

## Image processing and performance
- [ ] Optimize naive `convolve`, `blur`, and resize in shim or move to OpenCV equivalents
- [ ] Add unit/perf tests for SC computation paths (8-bit, 16-bit, temporal)

## UI/UX
  - [x] Replace About dialog CImg version with shim label or remove
- [ ] Add option to toggle OpenCV/Qt backends if both are present

## Camera and video
- [ ] Verify USB/video-in with OpenCV capture devices (exposure, FPS)
- [ ] Validate Basler/Pylon path after image changes

## Build, packaging, CI
- [ ] Optional: Windows build with Qt6 and OpenCV via vcpkg

## macOS setup
- [ ] Install Homebrew and run `brew update`
- [ ] Install required packages via Homebrew: `cmake`, `ninja`, `qt`, `opencv`
- [ ] (Optional) Install Basler Pylon SDK and/or NI-DAQmx for hardware support