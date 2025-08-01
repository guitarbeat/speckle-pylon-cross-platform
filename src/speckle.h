#include <QTextStream>
#ifndef SPECKLECLASS_H
#define SPECKLECLASS_H

#include <QColor>
#include <string.h>
#include "camera.h"
#include "SpeckleROIClass.h"
#include "SpeckleOverlayClass.h"
#include "acquisitionclass.h"
#include "cameradescription.h"

#ifdef _WIN32
#include <Windows.h>
#endif

// opencv should come before CImg
#ifdef SPECKLE_USE_OPENCV
#include "openCVGrabber.h"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace cv;

#ifdef _WIN32
#include <dshow.h>
#pragma comment(lib, "strmiids")
#endif

#endif

#include "CImg.h"
using namespace cimg_library;

//#include <QCameraInfo>

#ifdef USE_FLSCI
#include "flsci.h"
#endif

#ifdef USE_NIDAQ
#include <NIDAQmx.h>
#include "DOPulseGenerator.h"
#endif

#ifdef USE_MESI
#include "mesi.h"
#endif

#ifdef USE_LIGHTCRAFTER
#include "dmd.h"
#endif

#ifdef USE_PYLON
#include "pylonclass.h"
#endif

#include "speckle_defines.h"

class SpeckleClass : public QObject
{
	Q_OBJECT

public:
    SpeckleClass();
#ifdef USE_PYLON
    PylonClass pylonCamera;
    PylonClass wl_pylonCamera; // pylon camera for white light
#endif
#ifdef SPECKLE_USE_OPENCV
    OpenCVGrabber openCVCamera;
    OpenCVGrabber wl_openCVCamera; // usb camera for white light
#endif

    Camera simulatedCamera;
    Camera *theCamera;

    AcquisitionClass *acquisition;
    SpeckleOverlayClass overlays;
    QList<cameraDescription> cameras_available;
	
    CImgList<unsigned char> raw_list;
    CImgList<unsigned short> raw_list16;
    unsigned char *raw_images[MAX_NUMBER_IMG_BUFFERS];
    CImgList<unsigned char> video_in_frames_to_write; // Video input frame storage

    float *rTC_base;
    float *rTC;
	float frame_rate;
	float SC_max, SC_min;
    int raw_min, raw_max;
	float TC_max, TC_min;
    float ratio_min, ratio_max;

    // to be moved to AcquisitionClass
    int Nframes, Nreps;
    long img_written, sc_img_written;
    int acquire_flag;
    int pause_acquisition;
    //float *acquisition_times;
    QVector<float> acquisition_times;
#ifdef _WIN32
    SYSTEMTIME acq_time;
#endif

    // to be moved to ProcessingClass
    int NxN; // size of moving window. used to be called Navg
    // speckle processing variables
    unsigned short sc_h, sc_w; // size of sc and tc images
    float *SC;
    void *SC_free; // ptr for freeing *SC
    int sc_processed; // number of images processed
    int num_sc_to_avg; // number of raw frames to average for each sc image
    int process_mode;
    int last_raw_processed; // index of the last raw frame processed
    int num_raw_processed; // total # of raw images processes
    int num_sc_processed; // number of sc images generated so far
    float *sc_images[MAX_NUMBER_IMG_BUFFERS]; // array of buffers to hold sc data
    float *sc_moving;
    int moving_avg_width;
    int num_sc_buffers_allocated;
    QVector<float> sc_acquisition_times;
    bool fast_sc;
    bool temporal_sc;
    int num_processing_threads;
#ifdef USE_FLSCI
    flsci_sc sc_calc;
    flsci_rct rct_calc;
    float *rct_table;
#endif

    // variables for enabling frame capture from webcams
#ifdef SPECKLE_USE_OPENCV
    cv::VideoCapture capture_device;
    Mat captured_frame;
#endif
    CImg<unsigned char> captured_rgb;
    CImgList<float> video_in_ctrl_pts, sc_ctrl_pts;
    CImg<float> VideoTform;
    CImg<int> VideoPixelMapping;
    int VideoPixel_min_w, VideoPixel_max_w, VideoPixel_min_h, VideoPixel_max_h; // bounding box values for pixel mapping
    int video_in_device_number;    
    CImgList<unsigned char> overlay_frames_to_write;
    CImgList<unsigned char> sc_frames_to_write;
    bool save_overlay_video, save_sc_video, save_input_video;
    int overlay_frames_shown, sc_frames_shown;
    int sc_frames_buffered;
    int VideoFileFormat;
    int video_in_frames_acquired;
    QVector<float> video_in_acquisition_times;

    bool show_raw;
    bool save_raw;
    bool compute_SC;
    bool show_SC;
    bool save_SC;
    bool show_rTC;
    bool show_overlay;
	int write_mode;
	int Nimg_per_buffer;

    int sc_ready_for_display;
    bool rTC_ready_for_display;
    bool overlay_ready_for_display;
	int update_live;
	bool update_roi_plot;
    bool autoset_baseline;

	QString filename; // base filename 
	int filename_format;
    bool autoincrement_filename;
	double t_start; // start time in seconds

    CImg<unsigned char> live_img, live_img_rgb;
    CImg<unsigned short> live_img16;
    CImg<unsigned char> sc_img, sc_img_rgb;
    CImg<unsigned char> ratio_img, ratio_img_rgb;
    CImg<unsigned char> overlay_img, overlay_img_rgb;
    CImg<unsigned char> jet_palette, gray_palette, cool_palette, reverse_jet_palette;
    CImg<unsigned char> hot_palette, autumn_palette, gray_sat_palette, pmkmp_palette;
    CImg<unsigned char> greens_palette;
    CImg<unsigned char> neon_palette, reverse_gray_palette;
    CImg<unsigned char> sc_palette, live_palette, tc_palette;
    CImg<float> sc_imgf, ratio_imgf, overlay_imgf;
	CImg<int> AOI_selection;
	int transpose, flip_horizontal, flip_vertical, rotate;
	int Imin, Imax;
    unsigned char red_chan, green_chan, blue_chan;
    int last_live_displayed;
    int mask_dark_areas_threshold;
    int mask_blur_width;
	
    bool show_hist = false;
    CImg<float> histogram_red, histogram_blue, histogram_green;
	int image_zoom;
	bool show_colorbars;
    bool show_sc_colorbar, show_raw_colorbar;
    bool duplicate_sc_window, duplicate_overlay_window;

	QList<SpeckleROIClass *> ROI_list;
	QList<QColor> ROI_color_list;
    bool enable_ROI_plot, enable_ROI_plot_save, autoscale_roi_plot, autoscale_roi_rel_plot, show_full_ROI_plot, roi_plot_baseline;
	float roi_max, roi_min, roi_rel_max, roi_rel_min;
    int roi_plot_limit, roi_plot_offset;
    int roi_plot_baseline_start, roi_plot_baseline_end;

    // NI-DAQmx Variables
#ifdef USE_NIDAQ
    PulseGenerator pulse_gen;
    uInt64 samples_per_channel;
    uInt64 daq_samples_per_illum_region;
    uInt64 daq_decays_per_illum_region;
#endif

    bool daq_is_avail;
	bool disable_daq;
	//bool enable_daq;
	bool start_daq_with_camera, stop_daq_with_camera;
	double daq_samp_rate;
	float daq_duration;
	QStringList daq_dev_list;
	QStringList daq_dev_names;
	QStringList daq_ai_chan_list;
	QString daq_use_ai_chan_list;
	int curr_daq_dev_index;
	int num_daq_chan_in_use;
	double daq_max_ai_samp_rate;
	QVector<double> daq_data;
	int daq_status, daq_mode;
	int daq_output_file_format;
	long daq_samples_read;
	int ai_input_config;
	int daq_samples_per_trigger;
	QVector<short> daq_data16;
	double daq_AOM_pulse_rate;
	double daq_AOM_voltage;
	double daq_AOM_pulse_width;
	int daq_AOM_mode; // time or freq domain
	//double daq_elapsed_time;
	QVector<double> ao_vec;
	QVector<double> ao_freq_list; // frequencies used in freq domain pO2
	double daq_AOM_offset; // offset voltage for freq domain pO2
	bool daq_write_continuously;
    QString daq_task_name1;
    QString daq_task_name2;
    int daq_camera_delay; // delay in ms
    int seq_delay; // delay in s

	// command line arguments
	QString command_line;		

	// public functions
	void init_colormaps(void);
	//void gen_rand(int);	
	void Write_SpeckleContrast(QString);
    void Write_TC(QString);
	void AddToLogFile(char *);
    void AddToLogFile(QString);
    void SetupMemoryBuffers(void);
    QString GetDateTimeFilename(void);
    void Set_sc_width_height(void);
    void setRawColormap(QString cmap_string);
    void setRawColormap(int idx);
    void setSCColormap(QString cmap_string);
    void setSCControlPoints(QPolygonF poly);
    void setVideoInControlPoints(QPolygonF poly);
    void setCamera(cameraDescription c);
    void findAvailableCameras(void);
    bool saveAnything(void);

#ifdef USE_MESI
    MESI theMESI;
#endif

#ifdef USE_LIGHTCRAFTER
    DMD theDMD;
    bool calibration_flag_dmd;  // Flag indicating next dmd calibration point should be selected
    bool calibration_flag_ccd;  // Flag indicating projected point should be identified
    bool dmd_tile_flag;         // Flag to indicate that DMD tile selection should initiate
#endif

#ifdef SPECKLE_USE_OPENCV
    void registerCamerasFromQRCodes(void);
#endif

signals:
    void videoInCtrlPointsChangedFromQR(QPolygonF polygon);
    void scCtrlPointsChangedFromQR(QPolygonF polygon);
    void speckleAOIChanged(void);

public slots:
    void setupCameraAOI(QRectF rect);

private:


#ifdef SPECKLE_USE_OPENCV
    QStringList getVideoDeviceNames(void);
#endif

};

#endif



