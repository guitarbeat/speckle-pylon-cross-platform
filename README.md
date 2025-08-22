# Speckle Software

The Speckle Software is a program for performing [laser speckle contrast imaging](https://foil.bme.utexas.edu/research/laser-speckle-contrast-imaging). It provides control over an acquisition camera and processes raw image data into speckle contrast imagery in real-time. The program is written in C++ and designed to run on modern Windows computers using Basler cameras.

An experimental port to Qt6 and OpenCV is underway to enable Linux support. The Windows instructions below remain valid for the original Qt5 build, while the experimental Linux build uses CMake and modern Qt6 packages.

Developed at the University of Texas at Austin in Dr. Andrew Dunn's [_Functional Optical Imaging Laboratory_](https://foil.bme.utexas.edu/) in the Department of Biomedical Engineering.

## Overview

* [Experimental Linux Build](#experimental-linux-build)
* [Developing the Speckle Software](#developing-the-speckle-software)
    * [Install Prerequisites](#install-prerequisites)
    * [Optional Installations](#optional-installations)
    * [Setup Qt Project](#setup-qt-project)
    * [Building for Release](#building-for-release)
* [Using the Speckle Software](#using-the-speckle-software)

## Experimental Linux Build

The cross-platform port uses CMake with Qt6 and OpenCV. These steps have been tested on Debian/Ubuntu-like distributions and remain a work in progress.

### Prerequisites

- Qt 6 development packages (for example: `qt6-base-dev` and `qt6-5compat-dev`)
- OpenCV 4 development package (`libopencv-dev`)
- CMake 3.16 or newer and a C++17 compiler
- Optional: Basler [Pylon SDK](https://www.baslerweb.com/en/products/software/) and NI-DAQmx for camera and DAQ features

### Configure and Build

```bash
git clone https://github.com/UTFOIL/speckle-pylon-cross-platform.git
cd speckle-pylon-cross-platform
cmake -S . -B build
cmake --build build
```

The resulting binary `build/speckle` is linked against Qt6 and OpenCV. Feature toggles such as `SPECKLE_USE_PYLON` and `SPECKLE_USE_NIDAQ` can be enabled with `-D` flags when running CMake.

### Migration Status

The Linux port replaces the original CImg dependency with a small compatibility shim and builds against Qt6 and OpenCV. OpenCV usage is currently required, and several Windows-specific paths remain guarded. Follow ongoing progress in [PROGRESS.md](PROGRESS.md).

## Developing the Speckle Software

### Install Prerequisites

1. Install [Visual Studio Community 2017](https://docs.microsoft.com/en-us/visualstudio/releasenotes/vs2017-relnotes)
   * Confirmed working with Visual Studio 2017 v15.9.16
   * Select the "Desktop Development with C++" workload (MSVC v141)
   * Launch Visual Studio 2017 to complete installation

2. Install [Qt Open Source](https://download.qt.io/archive/qt/)
   * Confirmed working with [Qt 5.13.0](https://download.qt.io/archive/qt/5.13/5.13.0/qt-opensource-windows-x86-5.13.0.exe)
   * Use default installation location: `C:\Qt\Qt5.13.0`
   * Install `MSVC 2017 64-bit`, `Qt Charts`, and `Qt Creator 4.9.1` components

3. Install [Basler Pylon Camera Software Suite](https://www.baslerweb.com/en/products/software/pylon-windows/)
   * Confirmed working with [Pylon 5.2.0](https://www.baslerweb.com/en/sales-support/downloads/software-downloads/pylon-5-2-0-windows/)
   * Select the "Developer" installation profile
   * Select USB and GigE interfaces
   * Install to default directory: `C:\Program Files\Basler\pylon 5\`

### Optional Installations

1. Install [Debugging Tools for Windows](https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/)
   * Download [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk) 
   * Only select "Debugging Tools for Windows" during installation

2. Install [NI-DAQmx Software](http://sine.ni.com/nips/cds/view/p/lang/en/nid/10181)
   * Enables support for signal recording, pulse generation, and MESI functionality
   * Confirmed working with NI-DAQmx 18.5.0
   * Install to default directory: `C:\Program Files (x86)\National Instruments\`

3. Install [NI Vision Acquisition Software](http://sine.ni.com/nips/cds/view/p/lang/en/nid/12892)
   * Enables support for Camera Link cameras (NI-IMAQ) and webcams (NI-IMAQdx)
   * Confirmed working with [NI Vision Acquisition Software 17.5](http://www.ni.com/download/ni-vision-acquisition-software-17.5/7270/en/)
   * Install to default directory: `C:\Program Files (x86)\National Instruments\`

4. Install [OpenCV](https://opencv.org/)
   * Enables support for external framegrabber for use with Overlay View
   * Confirmed working with [OpenCV 4.5.1](https://github.com/opencv/opencv/releases/tag/4.5.1)
   * Extract files to `C:\Software\opencv\`
      * If using different directory, update paths in `speckle.pro` file

5. Install [GitHub Desktop](https://desktop.github.com/)


### Setup Qt Project

1. Open Qt Creator and navigate to Tools > Options > Build & Run > Kits
   * There should be an auto-detected option (with errors)
      * _Desktop Qt 5.13.0 MSVC2017 64bit_
   * Select the appropriate C/C++ compiler for the architecture
      * _Microsoft Visual C++ Compiler 15.9.x (amd64)_
      * Note: Qt should automatically detect the initialization `vcvarsall.bat` for each compiler
   * If Debugging Tools for Windows was installed, the appropriate debugger should be automatically selected
     * Even if no debugger was detected the kit should now be valid

2. Use git or Github Desktop to clone the [speckle-software repository](https://github.com/UTFOIL/speckle-software) from Github
   * `git clone https://github.com/UTFOIL/speckle-software.git`

3. Open speckle.pro in Qt Creator
   * Configure the project to build the "Release" into the `speckle-software\build\` directory
   * "Debug" and "Profile" can be disabled (or built into the same directory)

![Qt Configure Project](https://user-images.githubusercontent.com/867617/143131249-b637da51-2450-42bb-a228-fa46bae9040d.png)


### Qt Project Build Settings

![Qt Project Settings](https://user-images.githubusercontent.com/867617/143131673-c733569e-3a38-48a0-a475-9c0f91d33d80.png)


### Building for Release

1. Update version number in [speckle.pro](src/speckle.pro)

```
# Application Version
VERSION_MAJOR = 3
VERSION_MINOR = 0
VERSION_BUILD = 0
```

2. Create tag for this release and push to remote

```
git tag -a v3.0.0 -m "Speckle v3.0.0 Release"
git push origin --tags
```

3. Enable desired config flags in [speckle.pro](src/speckle.pro) and build project
   * Disable debug console by commenting out `CONFIG += console`

4. Copy the executable and necessary DLLs to an archive (.zip)
   * If unsure which DLLs are necessary, run the program and try to delete everything in the release folder. Any resource currently in use is needed to operate the current build.
   * If using a different version of Qt from the one listed above, the Qt dependencies may need to be updated. This can be easily achieved using the [`windeployqt`](http://doc.qt.io/qt-5/windows-deployment.html) tool.

5. Use GitHub to create new release using the new tag

6. Discard all local changes related to the build process


## Using the Speckle Software

See the [Speckle Software Documentation](https://utfoil.github.io/speckle-software/) website. Source located on [`docs`](https://github.com/UTFOIL/speckle-software/tree/docs) branch.
