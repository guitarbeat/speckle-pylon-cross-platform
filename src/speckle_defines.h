#ifndef SPECKLE_DEFINES_H
#define SPECKLE_DEFINES_H

#define SPECKLE_VERSION 3.7
#define MAX_IMG_SIZE 4096

#define MAX_BUFFER_MEMORY 2000 // in Mb

//#define MAX_BUFFER_MEMORY 384000000
#define NUM_LIVE_SC_BUFFERS 64
#define MAX_NUMBER_IMG_BUFFERS 10000000 // 1e6
//#define MAX_BUFFER_MEMORY 1000000000
#define MAX_FILE_SIZE 256e6
#define HEADER_OFFSET 12288
#define SEQ_REP 0 // filename format
#define DATE_TIME 1 // filename format
#define TC_TABLE_SIZE 65536
#define PI 3.141592653589793
#define NUM_VIDEO_FRAME_BUFFERS 64


/**** acquire  flags ***/
enum {IDLE_MODE, FOCUS_MODE, ACQUISITION_MODE};
/***** colormap choices *****/
enum {GRAYSCALE, JET};
/***** colormap choices *****/
enum {WRITE_AFTER_SEQUENCE, WRITE_CONTINUOUS, WRITE_NEVER};
/***** trigger options *****/
enum {NO_TRIGGER, START_TRIGGER, STROBE_TRIGGER};
/**** daq output file format ******/
enum {MATLAB_OUTPUT, RAW_BINARY_OUTPUT};
/***** daq status **********/
enum {IDLE, ACQUIRING};
/**** daq modes *****/
enum {NO_DAQ, BASIC_DAQ, TRIGGERED_DAQ, TASK_DAQ, BASIC_DAQ_TDMS};
/**** output pulse trigger source for NI frame grabber ****/
enum {NO_PULSE, FRAME_START_PULSE, FRAME_STOP_PULSE};
/**** time or frequency domain specification for pO2 ****/
enum {TIME_DOMAIN, FREQ_DOMAIN};
/**** modes for speckle contrast processing ****/
enum {PROCESS_MOST_RECENT, PROCESS_PARALLEL, PROCESS_SERIAL};
/**** video output file format ****/
enum {VIDEO_MP4, VIDEO_AVI};

#endif // SPECKLE_DEFINES_H
