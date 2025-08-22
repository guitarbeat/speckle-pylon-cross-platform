# TODO

## Today
- [ ] Get Linux build green with Qt6/OpenCV: install deps, configure CMake, run build; capture compiler errors
- [ ] Add CMake option `SPECKLE_USE_PYLON` and guard Pylon includes/usages; add `find_package(Pylon)` on Linux if available
- [ ] Remove `CImg` usage from `src/pylonacquireasync.*` and `src/pylonclass.*`: use direct buffers or `cv::Mat`; ensure pixel ordering is correct
- [x] Update `README.md` with Linux instructions and current migration status

## In Progress
- [~] CImg → Qt6/OpenCV migration: build against Qt6/OpenCV on Linux
- [ ] Validate Basler/Pylon path after image representation changes

## Backlog
- [ ] Migrate remaining image code to `cv::Mat`/`QImage`; remove `CImg_to_QImage`
- [ ] Replace `draw_axis`/colorbar with Qt painting and remove shim no-op
- [ ] Optimize naive `convolve`, `blur`, and resize or move to OpenCV equivalents
- [ ] Add unit/perf tests for speckle computation paths (8-bit, 16-bit, temporal)
- [ ] CI workflow (Linux) to build and run basic tests
- [ ] Document Linux dependencies and add CMake presets
- [ ] Optional Windows build with Qt6/OpenCV via vcpkg
- [ ] UI: Replace About dialog CImg version with shim label or remove
- [ ] UI: Add option to toggle OpenCV/Qt backends if both are present
- [ ] Camera: Verify USB/video-in with OpenCV capture devices (exposure, FPS)
- [ ] Implement unconnected menu actions in `src/specklewindow.cpp` (export/import, ROI masks, etc.)
- [ ] CMake: Feature toggles for NI-DAQ, LightCrafter, FrameGrabber; guard platform-specific code
- [ ] Packaging: Produce Linux artifact (AppImage/DEB) and document runtime deps
- [x] Update `README.md` to reflect Qt6/Linux support and migration status

## Done
- [x] Add `TASKS.md`
- [x] Add `LESSONS_LEARNED.md`
