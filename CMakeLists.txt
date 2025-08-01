cmake_minimum_required(VERSION 3.16)

project(speckle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts OpenGL Core5Compat)
find_package(OpenCV REQUIRED)

add_executable(speckle
    src/main.cpp
    src/specklewindow.cpp
    src/specklewindow.h
    src/camera.cpp
    src/camera.h
    src/DaqThread.cpp
    src/DaqThread.h
    src/DOPulseGenerator.cpp
    src/DOPulseGenerator.h
    src/FrameGrabberClass.cpp
    src/FrameGrabberClass.h
    src/speckle.cpp
    src/speckle.h
    src/SpeckleROIClass.cpp
    src/SpeckleROIClass.h
    src/speckle_processing.cpp
    src/speckle_processing.h
)

target_include_directories(speckle PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Qt6_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
)

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

# Add these for debugging Qt issues
add_compile_definitions(QT_DEPRECATED_BY=QT_VERSION_CHECK(6,0,0))
add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=QT_VERSION_CHECK(6,0,0))

# Ensure position independent code for shared libraries
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")


