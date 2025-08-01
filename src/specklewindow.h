#ifndef SPECKLEWINDOW_H
#define SPECKLEWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QToolBar>
#include "speckledisplay.h"
#include "SpeckleSettings.h"
#include "HistogramWindow.h"
#include "ProcessingThread.h"
#include "WriteThread.h"
#include "WriteSCThread.h"
#include "speckle.h"
#include "liveimagecreator.h"
#include "overlayimagecreator.h"
#include "scimagecreator.h"

#ifdef SPECKLE_USE_OPENCV
#include "videointhread.h"
#include "WriteVideoThread.h"
#endif

//class SpeckleDisplay;

class SpeckleWindow : public QMainWindow
{
    Q_OBJECT

public:
    SpeckleWindow(QWidget *parent = nullptr);

    WriteThread write_thread;
    WriteSCThread write_sc_thread;
    ProcessingThread process_thread;

    // worker threads to create images for display
    QThread liveImageCreatorThread;
    LiveImageCreator *liveCreator;
    QThread scImageCreatorThread;
    SCImageCreator *scCreator;
    QThread overlayImageCreatorThread;
    OverlayImageCreator *overlayCreator;

#ifdef SPECKLE_USE_OPENCV
    VideoInThread video_in_thread;
    WriteVideoThread *write_sc_video_thread;
    WriteVideoThread *write_overlay_video_thread;
    WriteVideoThread *write_input_video_thread;
#endif

signals:
    void startAcquisition(void);
    void stopAcquisition(void);
    void isLive(bool status);
    void stopPressed(void);

private slots:
    // Thread slots
    void updateAcquisitionStatus(void);
    void addNewROI(QPolygonF polygon, QColor color);
    void updateSCControlPoints(QPolygonF polygon);
    void updateVideoInControlPoints(QPolygonF polygon);

    // Toolbar slots
    void on_actionLive(void);
    void on_actionStop(void);
    void on_actionRecord(void);
    void on_actionShowSettings(void);
    void on_actionShowHistogram(void);

    // Menu slots
    void exportRawImage(void);
    void exportSCImage(void);
    void exportOverlayImage(void);
    void showCameraInfo(void);
    void showAboutDialog(void);
    void saveSettings(void);
    void loadSettings(void);
    void showMissingActionAlert(void);

    // camera/acquisition slots
    void acquisitionComplete();
    void on_refreshCamerasAction();

    // Histogram slots
    void histogramClosed(void);

#ifdef SPECKLE_USE_OPENCV
    void on_actionAlignQR(void);
    void loadVideoTform(void);
    void saveVideoTform(void);
    void startStopVideoIn(void);
#endif

    // hotkey status
    void updateHotkeyStatus(void);

private:    
    SpeckleDisplay *display1, *display2, *display3;
    SpeckleSettings *settings;
    HistogramWindow *histogram;
    QProgressBar *acquisition_progressBar;
    QLabel *continuous_acq_label, *settings_label;
    QGraphicsView *view2;
    QSplitter *hSplitter;
    QSplitter *vSplitter;

    // Toolbar actions
    QAction *stopAction, *liveAction, *recordAction, *settingsAction,
            *histogramAction;
    QAction *fitInViewAction;

    // Menu actions
    QAction *setWorkingDirectoryAction, *setOutputFileAction, *exitAction,
            *processRawImagesAction, *openRawImagesAction,
            *openSCImagesAction, *exportRawImageAction,
            *exportSCImageAction, *exportOverlayImageAction,
            *exportRelativeImageAction, *exportRawImagesJPGAction,
            *exportSCImagesJPGAction, *importROIMasksAction,
            *exportROIMasksAction, *exportROIPlotDataAction,
            *saveSettingsAction, *loadSettingsAction,
            *aboutAction, *toggleFPSAction, *toggleColorbarAction,
            *loadVideoTformAction, *saveVideoTformAction,
            *cameraInfoAction, *refreshCamerasAction;

#ifdef SPECKLE_USE_OPENCV
    QAction *alignQRCodesAction;
#endif

    void init_speckle(void);
    void createActions(void);
    void createMenus(void);
    void createToolbar(void);
    void createStatusBar(void);
    void setupSignalsSlots(void);
    void prep_for_exit(void);
    void setupMainDisplay(void);
    void updateProgressBar(void);
    void readSettingsFile(QString fileName);
    void WriteLogFile(void);

protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *);
};

#endif // SPECKLEWINDOW_H


