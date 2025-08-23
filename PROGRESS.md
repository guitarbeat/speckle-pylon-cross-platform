## Speckle Linux port progress

### Status overview
- **Qt6 via aqtinstall, rootless CMake config**: Not confirmed
- **OpenCV optional; default SPECKLE_USE_OPENCV=OFF**: Not done (currently required and ON)
- **Vendored minimal OpenGL headers; headless includes**: Not found (links Qt6::OpenGL; no vendored GL headers)
- **CMake: add missing sources; guard platform/feature code**: Partial (Pylon/NIDAQ guarded; OpenCV not)
- **CImg compatibility shim (loops, hist, conv, map, draw, list API)**: Done
- **Windows-only guards; SYSTEMTIME stub; portable aligned alloc/free**: Done (minor leftovers behind optional features)
- **Logic/API mismatches fixed across key classes**: Partial (notably SystemTime_to_Seconds signature)
- **ROI fields/constructors; UI type/API corrections**: Done
- **Replace Sleep with QThread::msleep; guard OpenCV camera use**: Partial (msleep done; DaqThread still uses Sleep behind NIDAQ; VideoInThread needs full guards to disable OpenCV)
- **Successful Linux build of speckle**: Done

---

### Evidence and notes
- **Qt6 rootless/aQtInstall**: Project finds Qt6 via system paths; no aqtinstall hints.
```14:14:/workspace/CMakeLists.txt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts OpenGL Core5Compat)
```
```332:334:/workspace/build/linux/CMakeCache.txt
Qt6_DIR:PATH=/usr/lib/x86_64-linux-gnu/cmake/Qt6
```

- **OpenCV optionality (not yet)**: OpenCV is required; compile definition forces OpenCV paths ON.
```15:15:/workspace/CMakeLists.txt
find_package(OpenCV REQUIRED)
```
```69:69:/workspace/CMakeLists.txt
target_compile_definitions(speckle PRIVATE SPECKLE_USE_OPENCV)
```

- **OpenGL headers (vendored) and headless**: No vendored GL headers; links Qt6::OpenGL.
```115:124:/workspace/CMakeLists.txt
# Common Qt/OpenCV link
target_link_libraries(speckle PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Charts
    Qt6::OpenGL
    Qt6::Core5Compat
    ${OpenCV_LIBS}
)
```

- **CMake guards and sources**: Pylon/NIDAQ are properly option-guarded; OpenCV sources included unconditionally and feature is forced ON.
```81:107:/workspace/CMakeLists.txt
# Conditionally add Pylon sources and definitions
if(SPECKLE_USE_PYLON)
    target_compile_definitions(speckle PRIVATE USE_PYLON)
    ...
    find_package(Pylon QUIET)
    if(Pylon_FOUND)
        target_link_libraries(speckle PRIVATE Pylon::Pylon)
    else()
        message(WARNING "SPECKLE_USE_PYLON=ON but Pylon SDK was not found. Provide a Pylon CMake package or set PYLON_ROOT and add include/lib paths as needed.")
    endif()
endif()
```

- **CImg compatibility shim**: Present with loop macros, histogram, convolution, mapping, draw_image, transpose/mirror/rotate, and list API helpers.
```21:27:/workspace/src/CImg.h
static const char* cimg_version = "compat-0.1";
// Loop macros used in codebase
#define cimg_forX(img, x) for (int x = 0; x < (img).width(); ++x)
#define cimg_forXY(img, x, y) for (int y = 0; y < (img).height(); ++y) for (int x = 0; x < (img).width(); ++x)
#define cimg_forXYZ(img, x, y, z) for (int z = 0; z < (img).depth(); ++z) for (int y = 0; y < (img).height(); ++y) for (int x = 0; x < (img).width(); ++x)
```
```232:253:/workspace/src/CImg.h
// Naive convolution with float mask
template <typename M>
void convolve(const CImg<M>& mask, int /*boundary*/ = 0) {
    ...
}
```
```272:285:/workspace/src/CImg.h
// Histogram (returns bins-length float vector)
CImg<float> get_histogram(int bins, double minv, double maxv) const {
    ...
}
```
```298:310:/workspace/src/CImg.h
// Colormap mapping: current image must be 1-channel 2D; result becomes 3-channel RGB
void map(const CImg<uint8_t>& colormap) {
    ...
}
```
```162:173:/workspace/src/CImg.h
// Paste image at (x0,y0)
void draw_image(int x0, int y0, const CImg<T>& img) { ... }
```
```388:427:/workspace/src/CImg.h
// Minimal list of images (CImgList)
class CImgList { ... };
```

- **Windows-only guards and portable allocation**: SYSTEMTIME stub is provided; aligned alloc/free used on non-Windows; Windows API includes are guarded by `_WIN32` and Windows-only sources are not added to target.
```3:8:/workspace/src/speckle_processing.h
#ifdef _WIN32
#include "windows.h"
#else
#include <cstdint>
struct SYSTEMTIME { uint16_t wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds; };
#endif
```
```1267:1270:/workspace/src/SpeckleSettings.cpp
#ifdef _WIN32
    sc_tmp = (float *)_aligned_malloc(MAX_IMG_SIZE*MAX_IMG_SIZE*sizeof(float), 16);
#else
    sc_tmp = (float *)aligned_alloc(16, MAX_IMG_SIZE*MAX_IMG_SIZE*sizeof(float));
#endif
```
```1291:1294:/workspace/src/SpeckleSettings.cpp
#ifdef _WIN32
    _aligned_free(sc_tmp);
#else
    free(sc_tmp);
#endif
```

- **Logic/API mismatches in key classes**: Most classes compile and run under Linux; one mismatch remains for `SystemTime_to_Seconds` signature (header vs impl).
```22:22:/workspace/src/speckle_processing.h
double SystemTime_to_Seconds(SYSTEMTIME st);
```
```160:164:/workspace/src/speckle_processing.cpp
double SystemTime_to_Seconds(QTime qt)
{
    return qt.hour()*3600.0 + qt.minute()*60.0 + qt.second() + qt.msec()/1000.0;
}
```

- **ROI fields and constructors added**: Additional constructors and ROI fields including polygon and histogram-related buffers.
```24:27:/workspace/src/SpeckleROIClass.h
explicit SpeckleROIClass(QObject *parent = 0);
// Legacy constructor used by implementation
SpeckleROIClass(void);
```
```40:63:/workspace/src/SpeckleROIClass.h
QRectF ROI_rect;
QColor ROI_color;
QVector<float> ROI_data;
QVector<float> ROI_rel_data;
QString ROI_name;
float ROI_baseline;
float ROI_baseline_rel;
QPolygonF polygon;
...
QVector<double> sc_mean;
QVector<double> sc_mean_norm;
```

- **Replace Sleep with QThread::msleep; guard OpenCV use in VideoInThread**: `msleep` is used; an old `Sleep(50)` remains in `DaqThread` (compiled only if NIDAQ enabled). VideoInThread header is guarded, but `.cpp` references `openCVCamera` unconditionally (requires further guarding if OpenCV is OFF).
```60:62:/workspace/src/videointhread.cpp
else {
    QThread::msleep(5);
}
```
```66:67:/workspace/src/DaqThread.cpp
            Sleep(50);
```
```9:11:/workspace/src/videointhread.h
#ifdef SPECKLE_USE_OPENCV
#include "openCVGrabber.h"
#endif
```
```77:81:/workspace/src/videointhread.cpp
if(c.camera_type==CAMERA_FRAMEGRABBER)
{
    videoInCamera = &openCVCamera;
    videoInCamera->camera_name = c.description;
}
```

- **Successful Linux build**: Built binary present.
- Path: `/workspace/build/linux/speckle` (6.4 MB)
- **Runtime dependency issue**: Running the binary fails with `libQt6Charts.so.6` missing, so the Qt UI cannot launch.

---

### Follow-ups to fully satisfy the checklist
- Make OpenCV optional:
  - Add `option(SPECKLE_USE_OPENCV OFF)`, guard `find_package(OpenCV)` and sources, remove forced compile definition, and fix `VideoInThread` `.cpp` to wrap `openCVCamera` usage in `#ifdef SPECKLE_USE_OPENCV`.
- Remove or disable `Sleep(50)` in `DaqThread.cpp` (e.g., `QThread::msleep(50)` under Qt; only when NIDAQ path is compiled).
- Resolve `SystemTime_to_Seconds` signature mismatch (use a unified Qt-based signature or provide a SYSTEMTIME overload for Windows builds).
- Document and/or support aqtinstall-based Qt discovery (e.g., `CMAKE_PREFIX_PATH=$HOME/Qt/6.x.x/gcc_64`), or vendor cmake presets.
- Consider dropping `Qt6::OpenGL` if not required, or document/ensure headless-friendly runtime dependencies.
