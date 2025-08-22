#include <QtWidgets>
#include "specklewindow.h"
#include "speckledisplay.h"
extern SpeckleClass *speckle;

SpeckleWindow::SpeckleWindow(QWidget *parent)
    :QMainWindow(parent)
{
    display1 = new SpeckleDisplay(this);
    display1->setImgSrc(SpeckleDisplay::SC_IMG);
    display2 = new SpeckleDisplay(this);
    display2->setImgSrc(SpeckleDisplay::RAW_IMG);
    display3 = new SpeckleDisplay(this);
    display3->setImgSrc(SpeckleDisplay::OVERLAY_IMG);

    setupMainDisplay();
    setWindowTitle("Speckle Software");

    // Dialog containing all the controls
    settings = new SpeckleSettings;

    // Add main window menus and toolbar
    createActions();
    createToolbar();
    createMenus();
    createStatusBar();

    init_speckle();

    // Try loading default settings file
    QFileInfo default_settings("default.ini");
    if (default_settings.exists())
        readSettingsFile("default.ini");

    // image generation threads
    liveCreator = new LiveImageCreator;
    liveCreator->moveToThread(&liveImageCreatorThread);
    scCreator = new SCImageCreator;
    scCreator->moveToThread(&scImageCreatorThread);
    overlayCreator = new OverlayImageCreator;
    overlayCreator->moveToThread(&overlayImageCreatorThread);

    setupSignalsSlots();

    // START THREADS
    liveImageCreatorThread.start();
    scImageCreatorThread.start();
    overlayImageCreatorThread.start();
}
/*****************************************/
void SpeckleWindow::setupMainDisplay()
{
    hSplitter = new QSplitter;
    hSplitter->setHandleWidth(7);
    hSplitter->setStyleSheet("QSplitter::handle { image: url(://HandleVertical); border: 1px solid #999999; }");

    vSplitter = new QSplitter(Qt::Vertical);
    vSplitter->setHandleWidth(7);
    vSplitter->setStyleSheet("QSplitter::handle { image: url(://HandleHorizontal); border: 1px solid #999999; }");

    hSplitter->addWidget(display1);
    hSplitter->addWidget(vSplitter);
    vSplitter->addWidget(display2);
    vSplitter->addWidget(display3);

    setCentralWidget(hSplitter);
}
/*****************************************/
void SpeckleWindow::init_speckle(void) {

#ifdef USE_FLSCI
    speckle->rct_table = flsci_rct_table_create(TC_TABLE_SIZE);
    speckle->fast_sc = true;
#else
    speckle->fast_sc = false;
#endif

    speckle->acquire_flag = IDLE_MODE;

    speckle->transpose = 0;
    speckle->flip_horizontal = 0;
    speckle->flip_vertical = 0;
    speckle->rotate = 0;
    speckle->image_zoom = 100;
    speckle->last_live_displayed=0;

    speckle->Set_sc_width_height();

    speckle->raw_list.insert(1,0);
    speckle->raw_list[0].resize(speckle->theCamera->max_width,
                                speckle->theCamera->max_height,
                                speckle->theCamera->color_planes);
    speckle->raw_list16.insert(1,0);
    speckle->raw_list16[0].resize(speckle->theCamera->max_width,
                                  speckle->theCamera->max_height,
                                  speckle->theCamera->color_planes);
    speckle->raw_images[0] = speckle->raw_list[0].data();

    speckle->SC = static_cast<float*>(aligned_alloc(16, MAX_IMG_SIZE*MAX_IMG_SIZE*sizeof(float))); // 16-byte aligned
    speckle->rTC_base = (float *)calloc(MAX_IMG_SIZE*MAX_IMG_SIZE,sizeof(float));
    speckle->rTC = (float *)calloc(MAX_IMG_SIZE*MAX_IMG_SIZE,sizeof(float));

    speckle->sc_img.resize(speckle->sc_w, speckle->sc_h,1,1,0);
    speckle->sc_imgf.resize(speckle->sc_w, speckle->sc_h,1,1,0);
    speckle->sc_img_rgb.resize(speckle->sc_w, speckle->sc_h,1,3,0);
    speckle->live_img.resize(speckle->theCamera->im_w, speckle->theCamera->im_h,1,speckle->theCamera->color_planes,0);
    speckle->live_img16.resize(speckle->theCamera->im_w, speckle->theCamera->im_h,1,speckle->theCamera->color_planes,0);
    speckle->live_img_rgb.resize(speckle->theCamera->im_w, speckle->theCamera->im_h,1,3,0);

    speckle->autoincrement_filename = true;

    speckle->enable_ROI_plot = false;
    speckle->autoscale_roi_plot = true;
    speckle->autoscale_roi_rel_plot = true;

    speckle->show_full_ROI_plot = true;

    speckle->filename_format = SEQ_REP;
    speckle->red_chan = 255;
    speckle->green_chan = 0;
    speckle->blue_chan = 0;

    // Initialize colormaps
    speckle->init_colormaps();
    speckle->sc_palette = speckle->gray_palette;
    speckle->live_palette = speckle->gray_sat_palette;
    speckle->tc_palette = speckle->jet_palette;
    speckle->overlays.bg_cmap = speckle->gray_palette;

    speckle->show_rTC = false;
    speckle->temporal_sc=0;
    speckle->write_mode = WRITE_CONTINUOUS;  //  write_mode_combo->currentIndex();
    speckle->process_mode=PROCESS_MOST_RECENT;
    speckle->duplicate_sc_window=false;
    speckle->duplicate_overlay_window=false;

    speckle->show_raw_colorbar = false;
    speckle->show_sc_colorbar = false;
    speckle->sc_ready_for_display = 0;
    speckle->rTC_ready_for_display = false;
    speckle->overlay_ready_for_display = false;
    speckle->update_live = 0;
    speckle->seq_delay = 0; // default of 0 seconds delay between sequences

    // Initialize DMD functionality
#ifdef USE_LIGHTCRAFTER
    speckle->dmd_tile_flag = false;
    speckle->calibration_flag_dmd = false;
    speckle->calibration_flag_ccd = false;
#endif

#ifdef USE_NIDAQ
    connect(&daq_thread, SIGNAL(postSpeckleMessage(QString)),
            this, SLOT(updateStatusMessage(QString)));
    init_daq();
    setup_pulse_output_gui();
#else
    speckle->daq_is_avail = false;
    speckle->daq_mode = NO_DAQ;
#endif

#ifdef USE_MESI
    connect(mesi_ExposureInput,SIGNAL(editingFinished()),this,SLOT(validate_MESI_Exposures()));
#endif

#ifdef USE_LIGHTCRAFTER
    connect(&(speckle->theDMD),SIGNAL(postSpeckleMessage(QString)),this,SLOT(updateStatusMessage(QString)));
    connect(&(speckle->theDMD),SIGNAL(transformUpdated()),this,SLOT(updateTransformDisplay()));
    connect(&(speckle->theDMD),SIGNAL(maskUploaded(int)),this,SLOT(dmdPatternUploadProgressBar(int)));
    connect(&(speckle->theDMD),SIGNAL(finished()),this,SLOT(dmdPatternSequenceStart()));
//    connect(&display_thread,SIGNAL(ccd_calibration_point_known()),this,SLOT(dmdRegistration()));
//    connect(&display_thread,SIGNAL(dmd_calibration_point_known()),this,SLOT(show_dmd_calibration_pattern()));
//    connect(&display_thread,SIGNAL(tile_region_selected()),this,SLOT(dmdTileGenerate()));
    speckle->theDMD.initialize();
//    dmdTabUpdate();
#endif


    // video input settings
    speckle->VideoFileFormat=VIDEO_MP4;
}
/***************************************************************************************/
void SpeckleWindow::closeEvent(QCloseEvent *event) {

    if (speckle->acquire_flag == ACQUISITION_MODE)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Confirm Quit"),
                                      tr("Are you sure you want to quit? An acquisition is currently in progress."),
                                      QMessageBox::No | QMessageBox::Yes, QMessageBox::No);
        if (reply != QMessageBox::Yes)
        {
            event->ignore();
            return;
        }
    }

    prep_for_exit();
    event->accept();
    QApplication::closeAllWindows(); // Close all other windows
}
/***************************************************************************************/
void SpeckleWindow::resizeEvent(QResizeEvent *event) {
    //display->updateDisplay();
    QMainWindow::resizeEvent(event);
}
/***************************************************************************************/
void SpeckleWindow::createActions(void)
{

    // Live View
    liveAction = new QAction(QIcon(":/Live"), "Live View", this);
    liveAction->setToolTip("Live View (Ctrl + L)");
    liveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
    liveAction->setIconVisibleInMenu(false);
    connect(liveAction, &QAction::triggered,
            this, &SpeckleWindow::on_actionLive);

    // Record
    recordAction = new QAction(QIcon(":/Acquire"), "Record", this);
    recordAction->setToolTip("Record (Ctrl + R)");
    recordAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_R));
    recordAction->setIconVisibleInMenu(false);
    connect(recordAction, &QAction::triggered,
            this, &SpeckleWindow::on_actionRecord);

    // Stop
    stopAction = new QAction(QIcon(":/Stop"), "Stop", this);
    stopAction->setToolTip("Stop (Ctrl + S)");
    stopAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    stopAction->setIconVisibleInMenu(false);
    connect(stopAction, &QAction::triggered,
            this, &SpeckleWindow::on_actionStop);

    // Open Settings
    settingsAction = new QAction(QIcon(":/Settings"), "Show Settings", this);
    settingsAction->setToolTip("Open Settings");
    settingsAction->setIconVisibleInMenu(false);
    connect(settingsAction, &QAction::triggered,
            this, &SpeckleWindow::on_actionShowSettings);

    // Show Histogram
    histogramAction = new QAction(QIcon(":/Histogram"), "Histogram", this);
    histogramAction->setToolTip("Show Histogram (Ctrl + H)");
    histogramAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_H));
    histogramAction->setIconVisibleInMenu(false);
    connect(histogramAction, &QAction::triggered,
            this, &SpeckleWindow::on_actionShowHistogram);

    // Set Working Directory
    setWorkingDirectoryAction = new QAction("Set Working Directory", this);
    connect(setWorkingDirectoryAction, &QAction::triggered,
            settings, &SpeckleSettings::setWorkingDirectory);

    // Set Output File
    setOutputFileAction = new QAction("Set Output File", this);
    connect(setOutputFileAction, &QAction::triggered,
            settings, &SpeckleSettings::on_outputfile_browse_button_clicked);

    // Export Raw Image
    exportRawImageAction = new QAction("Export Raw Image", this);
    connect(exportRawImageAction, &QAction::triggered,
            this, &SpeckleWindow::exportRawImage);

    // Export SC Image
    exportSCImageAction = new QAction("Export SC Image", this);
    connect(exportSCImageAction, &QAction::triggered,
            this, &SpeckleWindow::exportSCImage);

    // Export Overlay Image
    exportOverlayImageAction = new QAction("Export Overlay Image", this);
    connect(exportOverlayImageAction, &QAction::triggered,
            this, &SpeckleWindow::exportOverlayImage);

    // Save Settings
    saveSettingsAction = new QAction("Save Settings", this);
    connect(saveSettingsAction, &QAction::triggered,
            this, &SpeckleWindow::saveSettings);

    // Load Settings
    loadSettingsAction = new QAction("Load Settings", this);
    connect(loadSettingsAction, &QAction::triggered,
            this, &SpeckleWindow::loadSettings);

    // Exit
    exitAction = new QAction("Exit", this);
    exitAction->setMenuRole(QAction::QuitRole);
    connect(exitAction, &QAction::triggered,
            qApp, &QApplication::closeAllWindows, Qt::QueuedConnection);

    // Show/Hide FPS Display
    toggleFPSAction = new QAction("Show Framerate", this);
    toggleFPSAction->setCheckable(true);
    toggleFPSAction->setChecked(true);
    connect(toggleFPSAction, &QAction::toggled,
            display1, &SpeckleDisplay::toggleFPSOverlay);
    connect(toggleFPSAction, &QAction::toggled,
            display2, &SpeckleDisplay::toggleFPSOverlay);
    connect(toggleFPSAction, &QAction::toggled,
            display3, &SpeckleDisplay::toggleFPSOverlay);

    // Show Camera Info
    cameraInfoAction = new QAction("Info", this);
    connect(cameraInfoAction, &QAction::triggered,
            this, &SpeckleWindow::showCameraInfo);

    // About
    aboutAction = new QAction("About", this);
    connect(aboutAction, &QAction::triggered,
            this, &SpeckleWindow::showAboutDialog);

#ifdef SPECKLE_USE_OPENCV
    // Align with QR codes
    alignQRCodesAction = new QAction("Align with QR Codes", this);
    alignQRCodesAction->setToolTip("Align with QR codes (Alt + Q)");
    alignQRCodesAction->setShortcut(QKeySequence(Qt::ALT | Qt::Key_Q));
    connect(alignQRCodesAction, &QAction::triggered,
            this, &SpeckleWindow::on_actionAlignQR);

    // Import Image Transform
    loadVideoTformAction = new QAction("Import Video Transform", this);
    connect(loadVideoTformAction, &QAction::triggered,
            this, &SpeckleWindow::loadVideoTform);

    // Export Image Transform
    saveVideoTformAction = new QAction("Export Video Transform", this);
    connect(saveVideoTformAction, &QAction::triggered,
            this, &SpeckleWindow::saveVideoTform);
#endif

    // Unconnected Actions

    // Process Raw Images
    processRawImagesAction = new QAction("Process Raw Images", this);
    connect(processRawImagesAction, &QAction::triggered,
            this, &SpeckleWindow::showMissingActionAlert);

    // Open Raw Images
    openRawImagesAction = new QAction("Open Raw Images", this);
    connect(openRawImagesAction, &QAction::triggered,
            this, &SpeckleWindow::showMissingActionAlert);

    // Open SC Images
    openSCImagesAction = new QAction("Open SC Images", this);
    connect(openSCImagesAction, &QAction::triggered,
            this, &SpeckleWindow::showMissingActionAlert);

    // Relative Image
    exportRelativeImageAction = new QAction("Export Relative Image", this);
    connect(exportRelativeImageAction, &QAction::triggered,
            this, &SpeckleWindow::showMissingActionAlert);

    // Export Raw Images as JPG
    exportRawImagesJPGAction = new QAction("Export Raw Images as JPG", this);
    connect(exportRawImagesJPGAction, &QAction::triggered,
            this, &SpeckleWindow::showMissingActionAlert);

    // Export SC Images as JPG
    exportSCImagesJPGAction = new QAction("Export SC Images as JPG", this);
    connect(exportSCImagesJPGAction, &QAction::triggered,
            this, &SpeckleWindow::showMissingActionAlert);

    // Import ROI Masks
    importROIMasksAction = new QAction("Import ROI Masks", this);
    connect(importROIMasksAction, &QAction::triggered,
            this, &SpeckleWindow::showMissingActionAlert);

    // Export ROI Masks
    exportROIMasksAction = new QAction("Export ROI Masks", this);
    connect(exportROIMasksAction, &QAction::triggered,
            this, &SpeckleWindow::showMissingActionAlert);

    // Export ROI Plot Data
    exportROIPlotDataAction = new QAction("Export ROI Plot Data", this);
    connect(exportROIPlotDataAction, &QAction::triggered,
            this, &SpeckleWindow::showMissingActionAlert);

    // Toggle Colorbar
    toggleColorbarAction = new QAction("Show Colorbar", this);
    toggleColorbarAction->setCheckable(true);
    toggleColorbarAction->setChecked(false);
    connect(toggleColorbarAction, &QAction::triggered,
            this, &SpeckleWindow::showMissingActionAlert);

    // refresh camera list
    // Align with QR codes
    refreshCamerasAction = new QAction("Refresh camera list", this);
    refreshCamerasAction->setToolTip("Refresh camera list (Alt + R)");
    refreshCamerasAction->setShortcut(QKeySequence(Qt::ALT | Qt::Key_R));
    connect(refreshCamerasAction, &QAction::triggered,
            this, &SpeckleWindow::on_refreshCamerasAction);
  //  qDebug() << "disabling camera list refresh for now...";
  //  refreshCamerasAction->setDisabled(true);
}
/***************************************************************************************/
void SpeckleWindow::showMissingActionAlert(void)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Warning");
    msgBox.setText("This feature has not been implemented.");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();
}
/***************************************************************************************/
void SpeckleWindow::createMenus(void)
{
    QMenu *fileMenu, *viewMenu, *cameraMenu, *helpMenu,
        *importSubMenu, *exportSubMenu, *settingsSubMenu;

    // File
    fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(setWorkingDirectoryAction);
    fileMenu->addAction(setOutputFileAction);
    fileMenu->addAction(processRawImagesAction);
    importSubMenu = fileMenu->addMenu("Import");
    importSubMenu->addAction(openRawImagesAction);
    importSubMenu->addAction(openSCImagesAction);
    importSubMenu->addSeparator();
    importSubMenu->addAction(importROIMasksAction);
#ifdef SPECKLE_USE_OPENCV
    importSubMenu->addSeparator();
    importSubMenu->addAction(loadVideoTformAction);
#endif
    exportSubMenu = fileMenu->addMenu("Export");
    exportSubMenu->addAction(exportRawImageAction);
    exportSubMenu->addAction(exportSCImageAction);
    exportSubMenu->addAction(exportOverlayImageAction);
    exportSubMenu->addAction(exportRelativeImageAction);
    exportSubMenu->addSeparator();
    exportSubMenu->addAction(exportRawImagesJPGAction);
    exportSubMenu->addAction(exportSCImagesJPGAction);
    exportSubMenu->addSeparator();
    exportSubMenu->addAction(exportROIMasksAction);
    exportSubMenu->addAction(exportROIPlotDataAction);
#ifdef SPECKLE_USE_OPENCV
    exportSubMenu->addSeparator();
    exportSubMenu->addAction(saveVideoTformAction);
#endif
    settingsSubMenu = fileMenu->addMenu("Settings");
    settingsSubMenu->addAction(settingsAction);
    settingsSubMenu->addAction(saveSettingsAction);
    settingsSubMenu->addAction(loadSettingsAction);
    fileMenu->addAction(exitAction);

    // View
    viewMenu = menuBar()->addMenu("View");
    viewMenu->addAction(toggleFPSAction);
    viewMenu->addAction(toggleColorbarAction);

    // Camera
    cameraMenu = menuBar()->addMenu("Camera");
    cameraMenu->addAction(liveAction);
    cameraMenu->addAction(stopAction);
    cameraMenu->addAction(recordAction);
    cameraMenu->addAction(cameraInfoAction);
#ifdef SPECKLE_USE_OPENCV
    cameraMenu->addAction(alignQRCodesAction);
#endif
    cameraMenu->addAction(refreshCamerasAction);

    // Help
    helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(aboutAction);
}
/***************************************************************************************/
void SpeckleWindow::createToolbar(void)
{
    QToolBar *toolbar = addToolBar("Speckle Controls");
    toolbar->setMovable(false);
    toolbar->addAction(liveAction);
    toolbar->addAction(stopAction);
    toolbar->addAction(recordAction);
    toolbar->addSeparator();
    toolbar->addAction(settingsAction);
    toolbar->addAction(histogramAction);
}
/*****************************************/
void SpeckleWindow::createStatusBar(void)
{
    statusBar()->showMessage("Idle");
    acquisition_progressBar = new QProgressBar;
    acquisition_progressBar->setVisible(false);
    statusBar()->addPermanentWidget(acquisition_progressBar);
    continuous_acq_label = new QLabel;
    continuous_acq_label->setVisible(false);
    statusBar()->addPermanentWidget(continuous_acq_label);
    settings_label = new QLabel;
    settings_label->setVisible(true);
    statusBar()->addPermanentWidget(settings_label);
}
/*****************************************/
void SpeckleWindow::setupSignalsSlots(void)
{

    // acquisition start
    connect(this, &SpeckleWindow::startAcquisition,
            liveCreator, &LiveImageCreator::startWatchAcquisition);
    connect(this, &SpeckleWindow::stopAcquisition,
            liveCreator, &LiveImageCreator::stopWatchAcquisition);
    connect(this, &SpeckleWindow::startAcquisition,
            scCreator, &SCImageCreator::startWatchAcquisition);
    connect(this, &SpeckleWindow::stopAcquisition,
            scCreator, &SCImageCreator::stopWatchAcquisition);
    connect(this, &SpeckleWindow::startAcquisition,
            overlayCreator, &OverlayImageCreator::startWatchAcquisition);
    connect(this, &SpeckleWindow::stopAcquisition,
            overlayCreator, &OverlayImageCreator::stopWatchAcquisition);
    connect(this, &SpeckleWindow::stopPressed,
            &write_thread, &WriteThread::stopWriting);
    connect(this, &SpeckleWindow::stopPressed,
            &write_sc_thread, &WriteSCThread::stopWriting);

    // Acquisition updates in status bar
    connect(speckle->acquisition, &AcquisitionClass::postAcquisitionStatus,
            this, &SpeckleWindow::updateAcquisitionStatus);

    connect(settings, &SpeckleSettings::rawSettingsChanged,
            liveCreator, &LiveImageCreator::updateLiveImage);
    connect(settings, &SpeckleSettings::scSettingsChanged,
            scCreator, &SCImageCreator::updateSCImage);
    connect(settings, &SpeckleSettings::overlaySettingsChanged,
            overlayCreator, &OverlayImageCreator::updateOverlayImage);

    // Connect signals to/from each SpeckleDisplay object
    foreach(SpeckleDisplay *display,  QObject::findChildren<SpeckleDisplay*>())
    {
        connect(liveCreator, &LiveImageCreator::liveImageReady,
                display, &SpeckleDisplay::updateRaw);
        connect(scCreator, &SCImageCreator::scImageReady,
                display, &SpeckleDisplay::updateSC);
        connect(overlayCreator, &OverlayImageCreator::overlayImageReady,
                display, &SpeckleDisplay::updateOverlay);
#ifdef SPECKLE_USE_OPENCV
        connect(&video_in_thread, &VideoInThread::videoinImageReady,
                display, &SpeckleDisplay::updateVideoIn);
#endif
        connect(this, &SpeckleWindow::isLive,
                display, &SpeckleDisplay::isLive);
        connect(display, &SpeckleDisplay::roiAdded,
                this, &SpeckleWindow::addNewROI);
        connect(settings, &SpeckleSettings::roiAdded,
                display, &SpeckleDisplay::addROI);
        connect(settings, &SpeckleSettings::roiRemoved,
                display, &SpeckleDisplay::removeROI);
        connect(settings, &SpeckleSettings::roiColorChanged,
                display, &SpeckleDisplay::updateROIColor);
        connect(settings, &SpeckleSettings::roiVisibilityToggled,
                display, &SpeckleDisplay::setROIVisibility);
        connect(display, &SpeckleDisplay::allROIVisibilityToggled,
                settings, &SpeckleSettings::toggleAllROIVisibility);
        connect(settings, &SpeckleSettings::showROICheckToggled,
                display, &SpeckleDisplay::toggleShowROICheck);
        connect(display, &SpeckleDisplay::scCtrlPointsChanged,
                this, &SpeckleWindow::updateSCControlPoints);
        connect(display, &SpeckleDisplay::videoCtrlPointsChanged,
                this, &SpeckleWindow::updateVideoInControlPoints);

        // communicate new control points for image registration from QR codes
        connect(speckle, &SpeckleClass::videoInCtrlPointsChangedFromQR,
                display, &SpeckleDisplay::setVideoCtrlPoints);
        connect(speckle, &SpeckleClass::scCtrlPointsChangedFromQR,
                display, &SpeckleDisplay::setSCCtrlPoints);
        connect(display, &SpeckleDisplay::cameraAOISelected,
                speckle, &SpeckleClass::setupCameraAOI);

        // toggle overlay visibility in display windows
        connect(display, &SpeckleDisplay::toggleHideOverlay,
                settings, &SpeckleSettings::toggleOverlaySource);

        // keyboard shortcuts from display windows to settings dialog
        connect(display, &SpeckleDisplay::incrementSCmin,
                settings, &SpeckleSettings::changeSCmin);
        connect(display, &SpeckleDisplay::incrementSCmax,
                settings, &SpeckleSettings::changeSCmax);
        connect(display, &SpeckleDisplay::incrementExposure,
                settings, &SpeckleSettings::changeExposure);
        connect(settings, &SpeckleSettings::infoUpdate,
                display, &SpeckleDisplay::updateInfo);
    }

    // signals from cameras. Each camera object\\'s signal must be connected to
    // acquisitionComplete slot. speckle->theCamera is a pointer so can\\'t connect to slot?
    connect(&(speckle->simulatedCamera), &Camera::acquisitionFinished,
            this, &SpeckleWindow::acquisitionComplete);
#ifdef USE_PYLON
    connect(&(speckle->pylonCamera), &PylonClass::acquisitionFinished,
            this, &SpeckleWindow::acquisitionComplete);
#endif
#ifdef SPECKLE_USE_OPENCV
    connect(&(speckle->openCVCamera), &OpenCVGrabber::acquisitionFinished,
            this, &SpeckleWindow::acquisitionComplete);
    connect(settings, &SpeckleSettings::colorCameraExpChanged,
            &video_in_thread, &VideoInThread::setCameraExposure);
    connect(settings, &SpeckleSettings::overlaySettingsChanged,
            this, &SpeckleWindow::startStopVideoIn);
#endif

    // update gui entries when camera AOI is set
    connect(speckle, &SpeckleClass::speckleAOIChanged,
            settings, &SpeckleSettings::setCameraAOIValues);

    // update statusbar when hotkeys are pressed
    connect(settings, &SpeckleSettings::hotkeyStatusUpdate,
            this, &SpeckleWindow::updateHotkeyStatus);

}
/****************************************************************************/
void SpeckleWindow::prep_for_exit(void) {

#ifdef USE_MESI // Set AOM voltage to zero and end DAQmx task
    speckle->theMESI.deactivateAOM();
#endif

#ifdef USE_LIGHTCRAFTER // Disconnect from LightCrafter
    if(speckle->theDMD.ready())
        speckle->theDMD.cleanup();
#endif

    // Disconnect from camera
    speckle->theCamera->cleanup();

    settings->close();
}
/*****************************************/
void SpeckleWindow::on_actionShowSettings(void)
{
    settings->show();
    settings->activateWindow();
}
/*****************************************/
void SpeckleWindow::on_actionShowHistogram(void)
{
    if(speckle->show_hist && histogram->isVisible()) // Window is open, raise it
        histogram->activateWindow();
    else // Create HistogramWindow
    {
        speckle->show_hist = true;
        histogram = new HistogramWindow();
        histogram->updateRawRange(speckle->Imin, speckle->Imax);
        histogram->updateSCRange(speckle->SC_min, speckle->SC_max);
        histogram->showOverlay(speckle->show_overlay);
        histogram->updateOverlay(speckle->overlays.GetOverMin(),
                                 speckle->overlays.GetOverMax(),
                                 speckle->overlays.useAlpha(),
                                 speckle->overlays.GetKmid());
        histogram->show();

        connect(liveCreator, &LiveImageCreator::histogramReady,
                histogram, &HistogramWindow::updateRawHistogram);
        connect(scCreator, &SCImageCreator::histogramReady,
                histogram, &HistogramWindow::updateSCHistogram);
        connect(histogram, &HistogramWindow::histogramClosed,
                this, &SpeckleWindow::histogramClosed);
        connect(settings, &SpeckleSettings::rawDisplayRangeChanged,
                histogram, &HistogramWindow::updateRawRange);
        connect(settings, &SpeckleSettings::scDisplayRangeChanged,
                histogram, &HistogramWindow::updateSCRange);
        connect(settings, &SpeckleSettings::overlayToggled,
                histogram, &HistogramWindow::showOverlay);
        connect(settings, &SpeckleSettings::overlayChanged,
                histogram, &HistogramWindow::updateOverlay);
    }
}
/*****************************************/
void SpeckleWindow::histogramClosed(void)
{
    speckle->show_hist = false;
}
/*****************************************/
void SpeckleWindow::on_actionStop(void)
{
    speckle->theCamera->stopAcquisition();
    speckle->acquire_flag = IDLE_MODE;
    statusBar()->showMessage("Idle");

    liveAction->setEnabled(true);
    recordAction->setEnabled(true);

    emit stopAcquisition();
    emit stopPressed();
    emit(isLive(false));
}
/*****************************************/
void SpeckleWindow::acquisitionComplete(void)
{
    // slot to handle acquisition finishing. Similar to on_actionStop, but this
    // is called when acquisition finishes rather than stop being pressed.
    speckle->acquire_flag = IDLE_MODE;
    statusBar()->showMessage("Idle");

    liveAction->setEnabled(true);
    recordAction->setEnabled(true);

    // Set progress bar to final acquisition number or duration
    updateProgressBar();

    emit stopAcquisition();
    emit(isLive(false));
}
/*****************************************/
void SpeckleWindow::on_actionLive(void)
{
    // extract all setttings from settings dialog
    speckle->setCamera(speckle->cameras_available[settings->getCameraIdx()]);
    settings->FillInCurrentValues();

    speckle->acquire_flag=FOCUS_MODE;
    speckle->SetupMemoryBuffers();
    speckle->acquisition->setStopCondition(AcquisitionClass::ACQUIRE_FOREVER);
    speckle->theCamera->initialize_acquisition(speckle->acquisition, speckle->raw_images,
                                               &speckle->acquisition_times);
    speckle->theCamera->acquireImagesAsync();
    if(speckle->compute_SC)
        process_thread.start();

#ifdef SPECKLE_USE_OPENCV
    if(speckle->show_overlay && speckle->overlays.bg_src==SRC_VIDEO)
    {
        video_in_thread.setCamera(speckle->overlays.bg_video_src);
        video_in_thread.start();
    }
#endif

    statusBar()->showMessage("Live");
    acquisition_progressBar->setVisible(false);
    continuous_acq_label->setVisible(false);

    emit startAcquisition();

    liveAction->setEnabled(false);
    recordAction->setEnabled(false);

    emit(isLive(true));
}
/*****************************************/
void SpeckleWindow::on_actionRecord(void)
{
    // extract all setttings from settings dialog
    settings->FillInCurrentValues();

    // Prompt to overwrite existing files
    if((speckle->saveAnything()) && speckle->filename_format == SEQ_REP && !speckle->autoincrement_filename) {
        QFileInfo raw_file(speckle->filename + ".00000");
        QFileInfo sc_file(speckle->filename + ".00000.sc");
        QFileInfo in_mp4_file(speckle->filename + "_input.mp4");
        QFileInfo sc_mp4_file(speckle->filename + "_sc.mp4");
        QFileInfo ol_mp4_file(speckle->filename + "_overlay.mp4");

        if(raw_file.exists() || sc_file.exists() || in_mp4_file.exists() || sc_mp4_file.exists() || ol_mp4_file.exists())
            if(QMessageBox::question(this, "Confirm Overwrite", "Overwrite " + speckle->filename + "?", QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
                return;
    }
    // automatically choose filename
    if(speckle->saveAnything() && speckle->filename_format == SEQ_REP && speckle->autoincrement_filename) {
        // find a base filename that\'s free
        int ifile=0;
        bool filename_avail=false;
        while(!filename_avail)
        {
            QFileInfo raw_file(speckle->filename + QString("%1").arg(ifile,3,10, QLatin1Char('0')) + ".00000");
            QFileInfo sc_file(speckle->filename + QString("%1").arg(ifile,3,10, QLatin1Char('0')) + ".00000.sc");
            QFileInfo in_mp4_file(speckle->filename + QString("%1").arg(ifile,3,10, QLatin1Char('0')) + "_input.mp4");
            QFileInfo sc_mp4_file(speckle->filename + QString("%1").arg(ifile,3,10, QLatin1Char('0')) + "_sc.mp4");
            QFileInfo ol_mp4_file(speckle->filename + QString("%1").arg(ifile,3,10, QLatin1Char('0')) + "_overlay.mp4");

            if(raw_file.exists() || sc_file.exists() || in_mp4_file.exists() || sc_mp4_file.exists() || ol_mp4_file.exists())
                ifile++;
            else
                filename_avail=true;
        }
        speckle->filename = speckle->filename + QString("%1").arg(ifile,3,10,QLatin1Char('0'));
    }

    // Initialize the progressbar
    acquisition_progressBar->reset();
    acquisition_progressBar->resetFormat();
    if(speckle->acquisition->stop_condition == AcquisitionClass::STOP_NUMBER)
    {
        acquisition_progressBar->setMaximum(speckle->acquisition->img_to_acquire);
        acquisition_progressBar->setFormat(QString("%p% (%v/%m)"));
        acquisition_progressBar->setVisible(true);
        continuous_acq_label->setVisible(false);
    }
    else if(speckle->acquisition->stop_condition == AcquisitionClass::STOP_TIME)
    {
        acquisition_progressBar->setMaximum(speckle->acquisition->max_acq_time);
        acquisition_progressBar->setFormat(QString("%p% (00:00/%1:%2)")
                                            .arg(speckle->acquisition->max_acq_time / 60000 , 2, 10, QLatin1Char('0'))
                                                                                          .arg((speckle->acquisition->max_acq_time % 60000) / 1000, 2, 10, QLatin1Char('0')));
        acquisition_progressBar->setVisible(true);
        continuous_acq_label->setVisible(false);
    }
    else if(speckle->acquisition->stop_condition == AcquisitionClass::ACQUIRE_FOREVER)
    {
        acquisition_progressBar->setVisible(false);
        continuous_acq_label->setVisible(true);
    }

    if(speckle->saveAnything())
        WriteLogFile();
    speckle->pause_acquisition=0;

    speckle->acquire_flag = ACQUISITION_MODE;

    speckle->SetupMemoryBuffers();
    speckle->theCamera->initialize_acquisition(speckle->acquisition, speckle->raw_images,
                                               &speckle->acquisition_times);
    speckle->theCamera->acquireImagesAsync();
    if(speckle->compute_SC)
        process_thread.start();

    statusBar()->showMessage("Acquiring");

    emit startAcquisition();

    // Start threads for continuous writing
    if(speckle->save_raw)
        write_thread.start();
    if(speckle->save_SC)
        write_sc_thread.start();

#ifdef SPECKLE_USE_OPENCV
    if(speckle->show_overlay && speckle->overlays.bg_src == SRC_VIDEO)
    {
        video_in_thread.setCamera(speckle->overlays.bg_video_src);
        video_in_thread.start();
    }

    if(speckle->show_overlay && speckle->save_overlay_video)
    {
        write_overlay_video_thread = new WriteVideoThread(speckle->filename + "_overlay.mp4",
                                                          &speckle->acquire_flag,
                                                          &speckle->overlay_frames_shown,
                                                          &speckle->overlay_frames_to_write);
        connect(write_overlay_video_thread, &QThread::finished,
                write_overlay_video_thread, &QObject::deleteLater);
        connect(this, &SpeckleWindow::stopPressed,
                write_overlay_video_thread, &WriteVideoThread::stopWriting);
        write_overlay_video_thread->start();
    }

    if(speckle->save_sc_video)
    {
        write_sc_video_thread = new WriteVideoThread(speckle->filename + "_sc.mp4",
                                                     &speckle->acquire_flag,
                                                     &speckle->sc_frames_buffered,
                                                     &speckle->sc_frames_to_write);
        connect(write_sc_video_thread, &QThread::finished,
                write_sc_video_thread, &QObject::deleteLater);
        connect(this, &SpeckleWindow::stopPressed,
                write_sc_video_thread, &WriteVideoThread::stopWriting);
        write_sc_video_thread->start();
    }

    if(speckle->save_input_video && speckle->show_overlay && speckle->overlays.bg_src == SRC_VIDEO)
    {
        write_input_video_thread = new WriteVideoThread(speckle->filename + "_input.mp4",
                                                        &speckle->acquire_flag,
                                                        &speckle->video_in_frames_acquired,
                                                        &speckle->video_in_frames_to_write);
        write_input_video_thread->saveTiming(&speckle->video_in_acquisition_times);
        write_input_video_thread->fixVFR(true);
        connect(write_input_video_thread, &QThread::finished,
                write_input_video_thread, &QObject::deleteLater);
        connect(this, &SpeckleWindow::stopPressed,
                write_input_video_thread, &WriteVideoThread::stopWriting);
        write_input_video_thread->start();
    }
#endif

    liveAction->setEnabled(false);
    recordAction->setEnabled(false);

    emit(isLive(true));
}
/****************************************************************************/
void SpeckleWindow::updateAcquisitionStatus(void)
{
    QStringList status;

    status << QString("Camera: %1 fps").arg(speckle->acquisition->getFPS());

#ifdef SPECKLE_USE_OPENCV
    if(video_in_thread.isRunning())
        status << QString("Video In: %1 fps").arg(video_in_thread.acquire_fps);
#endif

    if(speckle->compute_SC)
        status << QString("Processing: %1 fps").arg(process_thread.processing_fps);

    if(speckle->save_raw && speckle->acquire_flag == ACQUISITION_MODE)
        status << QString("Raw Write: %1 fps").arg(write_thread.raw_write_fps);

    if(speckle->save_SC && speckle->acquire_flag == ACQUISITION_MODE)
        status << QString("SC Write: %1 fps").arg(write_sc_thread.sc_write_fps);

#ifdef SPECKLE_USE_OPENCV
    if(speckle->acquire_flag == ACQUISITION_MODE)
    {
        if(speckle->save_sc_video)
            status << QString("SC Video Write: %1 fps").arg(write_sc_video_thread->get_write_fps());
        if(speckle->show_overlay)
        {
            if(speckle->overlays.bg_src == SRC_VIDEO && speckle->save_input_video)
                status << QString("Video In Write: %1 fps").arg(write_input_video_thread->get_write_fps());
            if(speckle->save_overlay_video)
                status << QString("Overlay Video Write: %1 fps").arg(write_overlay_video_thread->get_write_fps());
        }
    }
#endif

    statusBar()->showMessage("Acquiring (" + status.join(", ") + ")");

    if(speckle->acquire_flag == ACQUISITION_MODE)
        updateProgressBar();
}
/****************************************************************************/
void SpeckleWindow::updateHotkeyStatus(void)
{
    QString msg;
    //statusBar()->showMessage(QString("T=%1, K=[%2, %3]").arg(speckle->theCamera->exp_time)
    //                         .arg(speckle->SC_min).arg(speckle->SC_max));
    msg = QString("T=%1, K=[%2, %3], %4").arg(speckle->theCamera->exp_time)
            .arg(speckle->overlays.GetOverMin()).arg(speckle->overlays.GetOverMax())
            .arg(QFileInfo(speckle->filename).fileName());

    settings_label->setText(msg);
    if(speckle->acquire_flag == ACQUISITION_MODE)
        speckle->AddToLogFile(msg);
}
/****************************************************************************/
void SpeckleWindow::updateProgressBar(void)
{
    qint64 t_elapsed = speckle->acquisition->getTimeElapsed();
    if(speckle->acquisition->stop_condition == AcquisitionClass::STOP_NUMBER)
        acquisition_progressBar->setValue(speckle->theCamera->img_acquired);
    else if(speckle->acquisition->stop_condition == AcquisitionClass::STOP_TIME)
    {
        if(t_elapsed <= speckle->acquisition->max_acq_time)
            acquisition_progressBar->setValue(t_elapsed);
        else
            acquisition_progressBar->setValue(speckle->acquisition->max_acq_time); // Can\'t set value outside current range

        QString format = QString("%p% (%1:%2/%3:%4)")
                            .arg(t_elapsed / 60000 , 2, 10, QLatin1Char('0'))
                            .arg((t_elapsed % 60000) / 1000, 2, 10, QLatin1Char('0'))
                                                          .arg(speckle->acquisition->max_acq_time / 60000 , 2, 10, QLatin1Char('0'))
                              .arg((speckle->acquisition->max_acq_time % 60000) / 1000, 2, 10, QLatin1Char('0'));
        acquisition_progressBar->setFormat(format);
    }
    else if(speckle->acquisition->stop_condition == AcquisitionClass::ACQUIRE_FOREVER)
    {
        continuous_acq_label->setText(QString("%1 frames (%2:%3) ")
                                        .arg(speckle->theCamera->img_acquired)
                                        .arg(t_elapsed / 60000 , 2, 10, QLatin1Char('0'))
                                        .arg((t_elapsed % 60000) / 1000, 2, 10, QLatin1Char('0')));
    }
}
/****************************************************************************/
void SpeckleWindow::saveSettings(void)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Define settings save file (.ini)"),
                        nullptr, tr("Initialization Files (*.ini)"));

    if(fileName == nullptr)
        return;

    QSettings settingsToSave(fileName, QSettings::IniFormat);

    // Layout
    settingsToSave.setValue("hSplitter", hSplitter->saveState());
    settingsToSave.setValue("vSplitter", vSplitter->saveState());
    settingsToSave.setValue("display1_src", display1->getImgSrc());
    settingsToSave.setValue("display2_src", display2->getImgSrc());
    settingsToSave.setValue("display3_src", display3->getImgSrc());
    settingsToSave.setValue("show_fps", toggleFPSAction->isChecked());

    // Add values from SpeckleSettings
    settings->saveSettings(&settingsToSave);

    qDebug() << "Settings saved to" << fileName;
}
/****************************************************************************/
void SpeckleWindow::loadSettings(void)
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select settings file to load (.ini)"),
                        nullptr, tr("Initialization Files (*.ini)"));

    if(fileName != nullptr)
        readSettingsFile(fileName);
}
/****************************************************************************/
void SpeckleWindow::readSettingsFile(QString fileName)
{
    QSettings settingsToLoad(fileName, QSettings::IniFormat);

    // Layout
    hSplitter->restoreState(settingsToLoad.value("hSplitter").toByteArray());
    vSplitter->restoreState(settingsToLoad.value("vSplitter").toByteArray());
    display1->setImgSrc(settingsToLoad.value("display1_src", SpeckleDisplay::SC_IMG).toInt());
    display2->setImgSrc(settingsToLoad.value("display2_src", SpeckleDisplay::RAW_IMG).toInt());
    display3->setImgSrc(settingsToLoad.value("display3_src", SpeckleDisplay::OVERLAY_IMG).toInt());
    toggleFPSAction->setChecked(settingsToLoad.value("show_fps", true).toBool());

    // Load SpeckleSettings values
    settings->loadSettings(&settingsToLoad);
}
/****************************************************************************/
void SpeckleWindow::exportRawImage(void)
{
    QString fileName= QFileDialog::getSaveFileName(this, tr("Save Raw Image"),
                        nullptr, tr("Image Files (*.bmp *.png)"));
     if (!fileName.isNull())
     {
         QPixmap raw_qp = liveCreator->get_raw_qp();
         if (!raw_qp.save(fileName, nullptr, -1))
             qDebug() << "Error exporting raw image to" << fileName;
     }
}
/****************************************************************************/
void SpeckleWindow::exportSCImage(void)
{
    QString fileName= QFileDialog::getSaveFileName(this, tr("Save SC Image"),
                        nullptr, tr("Image Files (*.bmp *.png)"));
     if (!fileName.isNull())
     {
         QPixmap sc_qp = scCreator->get_sc_qp();
         if (!sc_qp.save(fileName, nullptr, -1))
             qDebug() << "Error exporting SC image to" << fileName;
     }
}
/****************************************************************************/
void SpeckleWindow::exportOverlayImage(void)
{
    QString fileName= QFileDialog::getSaveFileName(this, tr("Save Overlay Image"),
                        nullptr, tr("Image Files (*.bmp *.png)"));
     if (!fileName.isNull())
     {
         QPixmap overlay_qp = overlayCreator->get_overlay_qp();
         if (!overlay_qp.save(fileName, nullptr, -1))
             qDebug() << "Error exporting overlay image to" << fileName;
     }
}
/****************************************************************************/
void SpeckleWindow::addNewROI(QPolygonF polygon, QColor color)
{
    speckle->ROI_list.append(new SpeckleROIClass(nullptr));
    int i = speckle->ROI_list.size() - 1;
    speckle->ROI_list[i]->setPolygon(polygon);
    speckle->ROI_list[i]->set_color(color);
    settings->RefreshROIList();
}
/****************************************************************************/
void SpeckleWindow::updateSCControlPoints(QPolygonF polygon)
{
    speckle->setSCControlPoints(polygon);
}
/****************************************************************************/
void SpeckleWindow::updateVideoInControlPoints(QPolygonF polygon)
{
    speckle->setVideoInControlPoints(polygon);
}
/****************************************************************************/
void SpeckleWindow::showCameraInfo(void)
{
    QLabel *textbox = new QLabel;
    textbox->setText(speckle->theCamera->getCameraInfo());

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    layout->setContentsMargins(100, 25, 100, 25);
    layout->addWidget(textbox);

    QDialog about(this);
    about.setWindowFlags(about.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    about.setModal(true);
    about.setWindowTitle(tr("Camera Info"));
    about.setLayout(layout);
    about.exec();
}
/****************************************************************************/
void SpeckleWindow::showAboutDialog(void) {
    QLabel *icon = new QLabel;
    icon->setPixmap(QPixmap("://icons/splash.png"));

#ifdef USE_NIDAQ
    // Get current NI-DAQmx version
    uInt32 daqmx_major, daqmx_minor;
    DAQmxGetSysNIDAQMajorVersion(&daqmx_major);
    DAQmxGetSysNIDAQMinorVersion(&daqmx_minor);
#endif

    QLabel *text = new QLabel;
    text->setWordWrap(true);
    text->setText(QString("<p>&copy; %1 The University of Texas at Austin</p>").arg(QDate::currentDate().year()) +
                  QString("<p><a href=\'https://foil.bme.utexas.edu/\'>https://foil.bme.utexas.edu/</a></p>") +
                                     QString("<p>Build %1.%2.%3").arg(3).arg(1).arg(1) +
                  QString(" (%1)</p>").arg(QDate::currentDate().toString(Qt::ISODate)) +
                  QString("<p>Qt v%1</p>").arg(QT_VERSION_STR) +
#ifdef SPECKLE_USE_OPENCV
                  QString("<p>OpenCV %1</p>").arg(CV_VERSION) +
#endif
#ifdef USE_PYLON
                  QString("<p>Pylon %1</p>").arg(Pylon::GetPylonVersionString()) +
#endif
#ifdef USE_NIDAQ
                  QString("<p>NI-DAQmx %1.%2</p>").arg(daqmx_major).arg(daqmx_minor) +
#endif
#ifdef USE_NIIMAQDX
                  QString("<p>NI-IMAQdx</p>") +
#endif
#ifdef USE_NIIMAQ
                  QString("<p>NI-IMAQ</p>") +
#endif
#ifdef USE_LIGHTCRAFTER
                  QString("<p>TI DLP LightCrafter</p>") +
#endif
                  QString("")
    );

    QHBoxLayout *topLayout = new QHBoxLayout;
   // topLayout->setMargin(10);
    topLayout->setSpacing(10);
    topLayout->addWidget(icon);
    topLayout->addWidget(text);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);

    QDialog about(this);
    about.setWindowFlags(about.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    about.setModal(true);
    about.setWindowTitle(tr("About Speckle Software"));
    about.setLayout(mainLayout);
    about.exec();
}
 /****************************************************************************/
void SpeckleWindow::WriteLogFile(void)
{

  QFile file(speckle->filename+".log");

  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream out(&file);

  out << "----------------------------------\n";
  out << QDateTime::currentDateTime().toString()  << "\n";
  out << "------- Input Parameters ---------\n";
  out << "Raw Image Width=" << speckle->theCamera->im_w << ", Raw Image Height=" << speckle->theCamera->im_h << "\n";
  out << "SC Image Width=" << speckle->sc_w << ", SC Image Height=" << speckle->sc_h << "\n";
  out << "Exposure Time=" << speckle->theCamera->exp_time << "\n";
  out << "Top=" << speckle->theCamera->top << ", Left=" << speckle->theCamera->left << ", Width=" << speckle->theCamera->im_w << ", Height=" << speckle->theCamera->im_h <<"\n";
  out << "Output Filename: " << speckle->filename << "\n";

  if(speckle->acquisition->stop_condition == AcquisitionClass::STOP_NUMBER)
  {
      out << "Total images acquired: " << speckle->acquisition->img_to_acquire << "\n";
  }
  if(speckle->acquisition->stop_condition == AcquisitionClass::STOP_TIME)
      out << "Total acquisition time (mm:ss): " << QDateTime::fromMSecsSinceEpoch(speckle->acquisition->max_acq_time, Qt::UTC).toString("mm:ss") << "\n";

  // write transform
  if(!(speckle->VideoTform.is_empty()))
  {
      float a00 = speckle->VideoTform(0,0);
      float a01 = speckle->VideoTform(1,0);
      float b00 = speckle->VideoTform(2,0);
      float a10 = speckle->VideoTform(0,1);
      float a11 = speckle->VideoTform(1,1);
      float b10 = speckle->VideoTform(2,1);
      out.setRealNumberNotation(QTextStream::SmartNotation);
      out.setFieldWidth(16);
      out.setFieldAlignment(QTextStream::AlignLeft);
      out << "Video Transform (a00, a01, b00, a10, a11, b10):\n" ;
      out << a00 << a01 << b00 << a10 << a11 << b10;
  }
  file.close();

}
/***************************************************************************/
void SpeckleWindow::on_refreshCamerasAction(void)
{
    speckle->findAvailableCameras();
    settings->listAvailableCameras();
}
/****************************************************************************/
//
//
// BEGIN OPENCV CODE
//
#ifdef SPECKLE_USE_OPENCV
/***************************************************************************/
void SpeckleWindow::on_actionAlignQR(void)
{
    speckle->registerCamerasFromQRCodes();
}
/***************************************************************************/
void SpeckleWindow::saveVideoTform(void)
{
    if(speckle->VideoTform.is_empty())
        return;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),NULL, tr("Text files (*.txt)"));
    if(fileName.isEmpty())
        return;

    float a00 = speckle->VideoTform(0,0);
    float a01 = speckle->VideoTform(1,0);
    float b00 = speckle->VideoTform(2,0);
    float a10 = speckle->VideoTform(0,1);
    float a11 = speckle->VideoTform(1,1);
    float b10 = speckle->VideoTform(2,1);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return;
    QTextStream out(&file);
    out.setRealNumberNotation(QTextStream::SmartNotation);
    out.setFieldWidth(16);
    out.setFieldAlignment(QTextStream::AlignLeft);
    out << a00 << a01 << b00 << a10 << a11 << b10 << Qt::endl;

    // write control points if they are present
    if(speckle->sc_ctrl_pts.size()>2 && speckle->video_in_ctrl_pts.size()>2)
    {
        CImgList<float> scpts = speckle->sc_ctrl_pts; // save some typing
        CImgList<float> vpts = speckle->video_in_ctrl_pts; // save some typing
        out << scpts[0](0) << scpts[0](1) << scpts[1](0) << scpts[1](1) << scpts[2](0) << scpts[2](1) << Qt::endl;
        out << vpts[0](0) << vpts[0](1) << vpts[1](0) << vpts[1](1) << vpts[2](0) << vpts[2](1);
    }

    file.close();
}
/****************************************************************************/
void SpeckleWindow::loadVideoTform(void)
{
    QString file = QFileDialog::getOpenFileName(
                         this,
                         "Select transform file",
                         NULL, tr("Text files (*.txt)"));
    if(file.isEmpty())
        return;
    if(speckle->overlays.setTransformFromFile(file))
        speckle->overlays.GeneratePixelMapping(speckle->captured_rgb, speckle->sc_imgf,
                                           speckle->VideoTform, &(speckle->VideoPixelMapping));
}
/****************************************************************************/
void SpeckleWindow::startStopVideoIn(void)
{
    // start video_in_thread if enable overlays is toggled during acquisition
    if(speckle->show_overlay && speckle->overlays.bg_src==SRC_VIDEO && !(video_in_thread.isRunning()))
    {
        qDebug() << "bg_src= " << speckle->overlays.bg_src << "in startStopVideoIn";
        video_in_thread.setCamera(speckle->overlays.bg_video_src);
        if(speckle->acquire_flag != IDLE_MODE)
            video_in_thread.start();
    }
}
/****************************************************************************/
#endif
//
// END OPENCV CODE
//
//
/***************************************************************************/




