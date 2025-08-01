CONFIG += flsci             # Enable FLSCI processing
#CONFIG += lightcrafter      # Enable support for TI DLP LightCrafter 3000
#CONFIG += mesi              # Enable MESI functionality (requires nidaq flag)

#CONFIG += nidaq             # Enable NI-DAQ data acquisition
#CONFIG += niimaq            # Enable NI-IMAQ Camera Link support
#CONFIG += niimaqdx          # Enable NI-IMAQdx camera support

#CONFIG += pylon5-gige       # Enable support for Basler Pylon v5 GigE cameras
#CONFIG += pylon5-usb        # Enable support for Basler Pylon v5 USB cameras
CONFIG += pylon7-usb        # Enable support for Basler Pylon v7 USB cameras

CONFIG += enable_opencv     # Enable support for USB cameras using OpenCV
#CONFIG += frame_grabber

#CONFIG += thorlabs          # Enable support for Thorlabs cameras

CONFIG += console           # Enable console debugging output
CONFIG -= debug_and_release
CONFIG += embed_manifest_exe

DEFINES += QT5
QT += core
QT += widgets
QT += multimedia
QT += charts

# Application Version
VERSION_MAJOR = 3
VERSION_MINOR = 1
VERSION_BUILD = 1

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
           "VERSION_MINOR=$$VERSION_MINOR"\
           "VERSION_BUILD=$$VERSION_BUILD"

VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}
QMAKE_TARGET_PRODUCT = "Speckle Contrast Imaging Software"
QMAKE_TARGET_COPYRIGHT = "\251 The University of Texas at Austin"

DESTDIR = ../build/release/
OBJECTS_DIR = ../build/tmp/
MOC_DIR = ../build/tmp/

HEADERS     = camera.h \
              acquisitionclass.h \
              CImg.h \
              cameradescription.h \
              HistogramWindow.h \
              imagegenerator.h \
              liveimagecreator.h \
              overlayimagecreator.h \
              ProcessingThread.h \
              scimagecreator.h \
              simulated_camera_class.h \
              speckle.h \
              speckle_defines.h \
              speckle_processing.h \
              speckledisplay.h \
              SpeckleOverlayClass.h \
              SpeckleROIClass.h \
              SpeckleSettings.h \
              specklewindow.h \
              WriteSCThread.h \
              WriteThread.h

SOURCES     = main.cpp \
              acquisitionclass.cpp \
              camera.cpp \
              cameradescription.cpp \
              HistogramWindow.cpp \
              imagegenerator.cpp \
              liveimagecreator.cpp \
              overlayimagecreator.cpp \
              ProcessingThread.cpp \
              scimagecreator.cpp \
              simulated_camera_class.cpp \
              speckle.cpp \
              speckle_processing.cpp \
              speckledisplay.cpp \
              SpeckleOverlayClass.cpp \
              SpeckleROIClass.cpp \
              SpeckleSettings.cpp \
              specklewindow.cpp \
              WriteSCThread.cpp \
              WriteThread.cpp

LIBS        += -luser32 -lshell32 -lgdi32

FORMS       = speckle.ui SpeckleSettings.ui

RESOURCES   += icons.qrc

RC_ICONS = "icons/speckle.ico"

DEFINES     += _CRT_SECURE_NO_WARNINGS

QMAKE_CXXFLAGS += -O2  ## force msvc to use optimizations
QMAKE_CXXFLAGS += -MP  ## enable parallel compilation

## Enable FLSCI processing
flsci {
    DEFINES += USE_FLSCI
    HEADERS += flsci.h
    INCLUDEPATH += 'lib/FLSCI'
    LIBS += 'lib/FLSCI/FLSCI64.lib'
}

## Enable opencv library functionality for image capture
enable_opencv {
    DEFINES += SPECKLE_USE_OPENCV cimg_use_opencv
    HEADERS += videointhread.h WriteVideoThread.h openCVGrabber.h openCVacquireasync.h
    SOURCES += videointhread.cpp WriteVideoThread.cpp openCVGrabber.cpp openCVacquireasync.cpp
    INCLUDEPATH += 'C:\Software\opencv\build\include'
    LIBS += -L'C:\Software\opencv\build\x64\vc15\lib'
    release {
        LIBS += opencv_world451.lib
    }
    debug {
        LIBS += opencv_world451d.lib
    }
    LIBS += ole32.lib oleaut32.lib strmiids.lib
}

## Enable raw image capture through frame grabber using opencv
frame_grabber {
    DEFINES += USE_FRAMEGRABBER
    HEADERS += FrameGrabberClass.h
    SOURCES += FrameGrabberClass.cpp
    TARGET = speckle_framegrabber
}

## Enable MESI functionality (requires nidaq flag)
mesi {
    DEFINES += USE_MESI
    HEADERS += mesi.h
    SOURCES += mesi.cpp
}

## Enable support for TI DLP LightCrafter 3000
lightcrafter {
    DEFINES += USE_LIGHTCRAFTER
    HEADERS += dmd.h common.h error.h
    SOURCES += dmd.cpp Tcp_client.c lcr_cmd.c lcr_packetizer.c
    LIBS += -lws2_32
}

## Enable NI-DAQ data acquisition
nidaq {
    DEFINES += USE_NIDAQ
    HEADERS += DaqThread.h DOPulseGenerator.h
    SOURCES += DaqThread.cpp DOPulseGenerator.cpp
    INCLUDEPATH += 'C:/Program Files (x86)/National Instruments/NI-DAQ/DAQmx ANSI C Dev/include'
    LIBS += 'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib64/msvc/NIDAQmx.lib'
}

## Enable NI-IMAQ (Camera Link) support
niimaq {
    DEFINES += USE_NIIMAQ
    INCLUDEPATH += 'C:/Program Files (x86)/National Instruments/NI-IMAQ/Include'
    LIBS += 'C:/Program Files (x86)/National Instruments/NI-IMAQ/Lib/MSVC/imaq.lib'
    TARGET = speckle_dalsa
}

## Enable NI-IMAQdx camera support
niimaqdx {
    DEFINES += USE_NIIMAQDX
    HEADERS += LogitechClass.h Unibrain.h
    SOURCES += LogitechClass.cpp
    INCLUDEPATH += 'C:/Program Files (x86)/National Instruments/NI-IMAQdx/Include'
    LIBS += 'C:/Program Files (x86)/National Instruments/NI-IMAQdx/lib/msvc/niimaqdx.lib' \
            ole32.lib oleaut32.lib strmiids.lib
    TARGET = speckle_niimaqdx
}

## Enable support for Basler Pylon v5 GigE cameras
pylon5-gige {
    DEFINES += USE_PYLON
    DEFINES += PYLON_USE_GIGE
    DEFINES += NDEBUG
    HEADERS += pylonclass.h  pylonacquireasync.h
    SOURCES += pylonclass.cpp pylonacquireasync.cpp
    INCLUDEPATH += 'C:/Program Files/Basler/pylon 5/Development/include'
    LIBS += -L'C:/Program Files/Basler/pylon 5/Development/lib/x64'
    TARGET = speckle_pylon5_GIGE
}

## Enable support for Basler Pylon v5 USB cameras
pylon5-usb {
    DEFINES += USE_PYLON
    DEFINES += PYLON_USE_USB3
    DEFINES += NDEBUG
    HEADERS += pylonclass.h pylonacquireasync.h
    SOURCES += pylonclass.cpp pylonacquireasync.cpp
    INCLUDEPATH += 'C:/Program Files/Basler/pylon 5/Development/include'
    LIBS += -L'C:/Program Files/Basler/pylon 5/Development/lib/x64'
    TARGET = speckle_pylon5_usb
}

## Enable support for Basler Pylon v5 USB cameras
pylon5-universal {
    DEFINES += USE_PYLON
    DEFINES += PYLON_USE_UNIVERSAL
    DEFINES += NDEBUG
    HEADERS += pylonclass.h pylonacquireasync.h
    SOURCES += pylonclass.cpp pylonacquireasync.cpp
    INCLUDEPATH += 'C:/Program Files/Basler/pylon 5/Development/include'
    LIBS += -L'C:/Program Files/Basler/pylon 5/Development/lib/x64'
    TARGET = speckle_pylon5
}

## Enable support for Basler Pylon v5 USB cameras
pylon7-usb {
    DEFINES += USE_PYLON
    DEFINES += PYLON_USE_USB3
    DEFINES += NDEBUG
    HEADERS += pylonclass.h pylonacquireasync.h
    SOURCES += pylonclass.cpp pylonacquireasync.cpp
    INCLUDEPATH += 'C:/Program Files/Basler/pylon 7/Development/include'
    LIBS += -L'C:/Program Files/Basler/pylon 7/Development/lib/x64'
    TARGET = speckle_pylon7_usb
}

## Enable support for Thorlabs cameras
thorlabs {
    DEFINES += USE_THORLABS
    DEFINES += NDEBUG
    INCLUDEPATH += 'C:/Program Files/Thorlabs/Scientific Imaging/Scientific Camera Support/Scientific Camera Interfaces/SDK/Native Compact Scientific Camera Toolkit/include'
    HEADERS += ThorlabsClass.h
    SOURCES += ThorlabsClass.cpp tl_camera_sdk_load.c
    TARGET = speckle_thorlabs
}
