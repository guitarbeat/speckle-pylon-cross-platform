cmake_minimum_required(VERSION 3.16)

project(speckle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Feature toggles
option(SPECKLE_USE_PYLON "Enable Basler Pylon camera support" OFF)
set(SPECKLE_PYLON_INTERFACE "USB3" CACHE STRING "Pylon interface to use: USB3, GIGE, or UNIVERSAL")
set_property(CACHE SPECKLE_PYLON_INTERFACE PROPERTY STRINGS USB3 GIGE UNIVERSAL)
option(SPECKLE_USE_NIDAQ "Enable NI-DAQ features" OFF)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts OpenGL Core5Compat)
find_package(OpenCV REQUIRED)

add_executable(speckle
    src/main.cpp
    src/specklewindow.cpp
    src/specklewindow.h
    src/camera.cpp
    src/camera.h
    src/speckle.cpp
    src/speckle.h
    src/SpeckleROIClass.cpp
    src/SpeckleROIClass.h
    src/SpeckleOverlayClass.cpp
    src/SpeckleOverlayClass.h
    src/speckle_processing.cpp
    src/speckle_processing.h
    src/speckledisplay.cpp
    src/speckledisplay.h
    src/ProcessingThread.cpp
    src/ProcessingThread.h
    src/WriteThread.cpp
    src/WriteThread.h
    src/WriteSCThread.cpp
    src/WriteSCThread.h
    src/HistogramWindow.cpp
    src/HistogramWindow.h
    src/acquisitionclass.cpp
    src/acquisitionclass.h
    src/cameradescription.cpp
    src/cameradescription.h
    src/icons.qrc
    # Additional sources required by specklewindow and camera
    src/SpeckleSettings.cpp
    src/SpeckleSettings.h
    src/SpeckleSettings.ui
    src/liveimagecreator.cpp
    src/liveimagecreator.h
    src/scimagecreator.cpp
    src/scimagecreator.h
    src/overlayimagecreator.cpp
    src/overlayimagecreator.h
    src/imagegenerator.cpp
    src/imagegenerator.h
    src/openCVGrabber.cpp
    src/openCVGrabber.h
    src/videointhread.cpp
    src/videointhread.h
    src/WriteVideoThread.cpp
    src/WriteVideoThread.h
    src/openCVacquireasync.cpp
    src/openCVacquireasync.h
)

# Ensure OpenCV code paths are enabled
target_compile_definitions(speckle PRIVATE SPECKLE_USE_OPENCV)

if(SPECKLE_USE_NIDAQ)
    target_compile_definitions(speckle PRIVATE USE_NIDAQ)
    target_sources(speckle PRIVATE
        src/DaqThread.cpp
        src/DaqThread.h
        src/DOPulseGenerator.cpp
        src/DOPulseGenerator.h
    )
endif()

# Conditionally add Pylon sources and definitions
if(SPECKLE_USE_PYLON)
    target_compile_definitions(speckle PRIVATE USE_PYLON)
    if(SPECKLE_PYLON_INTERFACE STREQUAL "USB3")
        target_compile_definitions(speckle PRIVATE PYLON_USE_USB3)
    elseif(SPECKLE_PYLON_INTERFACE STREQUAL "GIGE")
        target_compile_definitions(speckle PRIVATE PYLON_USE_GIGE)
    elseif(SPECKLE_PYLON_INTERFACE STREQUAL "UNIVERSAL")
        target_compile_definitions(speckle PRIVATE PYLON_USE_UNIVERSAL)
    endif()

    target_sources(speckle PRIVATE
        src/pylonclass.cpp
        src/pylonclass.h
        src/pylonacquireasync.cpp
        src/pylonacquireasync.h
    )

    # Try to locate Pylon SDK if available
    find_package(Pylon QUIET)
    if(Pylon_FOUND)
        target_link_libraries(speckle PRIVATE Pylon::Pylon)
        message(STATUS "Pylon found: enabling Pylon support")
    else()
        message(WARNING "SPECKLE_USE_PYLON=ON but Pylon SDK was not found. Provide a Pylon CMake package or set PYLON_ROOT and add include/lib paths as needed.")
    endif()
endif()

target_include_directories(speckle PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Qt6_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
)

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

set_target_properties(speckle PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
)

# Define deprecation flags using numeric constants to avoid function-style macros on command line
# 0xMMNNPP for version MM.NN.PP
target_compile_definitions(speckle PRIVATE
    QT_DISABLE_DEPRECATED_BEFORE=0x060000
    QT_DEPRECATED_WARNINGS_SINCE=0x060000
)

# Ensure position independent code for shared libraries
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")


