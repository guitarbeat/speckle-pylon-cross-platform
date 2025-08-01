
/**************************************************************************************************************************************************
*                                 Copyright © 2012 Texas Instruments Incorporated - http://www.ti.com/                                            *
***************************************************************************************************************************************************
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: *
*                                                                                                                                                 *
*    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.                 *
*                                                                                                                                                 *
*    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the        *
*    documentation and/or other materials provided with the distribution.                                                                         *
*                                                                                                                                                 *
*    Neither the name of Texas Instruments Incorporated nor the names of its contributors may be used to endorse or promote products derived      *
*    from this software without specific prior written permission.                                                                                *
*                                                                                                                                                 *
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          *
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT     *
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT         *
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    *
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE      *
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                                                           *
***************************************************************************************************************************************************/
/**
*
* @file    lcr_cmd.h
*
* @brief	Contains DM365 Command Interface declarations. These can be called from main or any other functions.
**/
/***************************************************************************************************************************************************/

#ifndef LCR_CMD_H_
#define LCR_CMD_H_

#include "common.h"
#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LCR_CMD_VERSION_STR_LEN		32
#define LCR_CMD_SOLUTION_NAME_LEN	32

#define	ONE_BPP_PTN_SIZE		52046
#define	TWO_BPP_PTN_SIZE		208006
#define	THREE_BPP_PTN_SIZE		208022
#define	FOUR_BPP_PTN_SIZE		208054
#define	FIVE_BPP_PTN_SIZE		416054
#define	SIX_BPP_PTN_SIZE		416182
#define	SEVEN_BPP_PTN_SIZE		416438
#define	EIGHT_BPP_PTN_SIZE		416950

    typedef enum
    {
        REV_DM365 = 0x00,
                    REV_FPGA = 0x10,
                               REV_MSP430 = 0x20,

                                        }
                                        LCR_Revision_t;

    typedef enum
    {
        PWR_NORMAL,
        PWR_STANDBY,
    } LCR_PowerMode_t;

    typedef enum
    {
        LED_RED,
        LED_GREEN,
        LED_BLUE,

    } LCR_LEDSelect_t;

    typedef enum
    {
        SOL_DELETE,
        SOL_LOAD,
        SOL_SET_DEFAULT,
    } LCR_SolutionCommand_t;

    typedef enum
    {
        DISP_MODE_IMAGE,		/* Static Image */
        DISP_MODE_TEST_PTN,		/* Internal Test pattern */
        DISP_MODE_VIDEO,		/* HDMI Video */
        DISP_MODE_VIDEO_INT_PTN,	/* Interleaved pattern */
        DISP_MODE_PTN_SEQ,		/* Pattern Sequence */
        DISP_NUM_MODES,
        DISP_MODE_SAME,

    } LCR_DisplayMode_t;

    typedef enum
    {
        TEST_PTN_FINE_CHECKER,		/* 0x0 - Fine Checkerboard */
        TEST_PTN_SOLID_BLACK,		/* 0x1 - Solid black */
        TEST_PTN_SOLID_WHITE,		/* 0x2 - Solid white */
        TEST_PTN_SOLID_GREEN,		/* 0x3 - Solid green */
        TEST_PTN_SOLID_BLUE,		/* 0x4 - Solid blue */
        TEST_PTN_SOLID_RED,			/* 0x5 - Solid red */
        TEST_PTN_VERTICAL_LINES,	/* 0x6 - Vertical lines (1-white, 7-black) */
        TEST_PTN_HORIZONTAL_LINES,	/* 0x7 - Horizontal lines (1-white, 7-black) */
        TEST_PTN_FINE_VERTICAL_LINES, /* 0x8 - Vertical lines (1-white, 1-black) */
        TEST_PTN_FILE_HORIZONTAL_LINES, /* 0x9 - Horizontal lines (1-white, 1-black) */
        TEST_PTN_DIAG_LINES,		/* 0xA - Diagonal lines */
        TEST_PTN_VERTICAL_RAMP,		/* 0xB - Vertical Gray Ramps */
        TEST_PTN_HORIZONTAL_RAMP,	/* 0xC - Horizontal Gray Ramps */
        TEST_PTN_ANXI_CHECKER,		/* 0xD - ANSI 4x4 Checkerboard */
        NUM_TEST_PTNS
    } LCR_TestPattern_t;


    typedef enum
    {
        TRIGGER_TYPE_SW,
        TRIGGER_TYPE_AUTO,
        TRIGGER_TYPE_EXTRNAL,
        TRIGGER_TYPE_EXTRNAL_INV,
        TRIGGER_TYPE_CAMERA,
        TRIGGER_TYPE_CAMERA_INV,
        /* External trigger + exposure on the same line */
        TRIGGER_TYPE_TRIG_EXP,
        NUM_TRIGGER_TYPES
    } LCR_TriggerType_t;

    typedef enum
    {
        TRIGGER_EDGE_POS,
        TRIGGER_EDGE_NEG
    } LCR_TriggerEdge_t;

    typedef enum
    {
        CAPTURE_STOP,
        CAPTURE_SINGLE,
        CAPTURE_STREAM,
    } LCR_CaptureMode_t;

    typedef uint8 LCR_PatternCount_t;

    typedef struct
    {
        uint8 BitDepth;
        LCR_PatternCount_t NumPatterns;
        uint8 InvertPatterns;
        uint8 InputTriggerType;
        uint32 InputTriggerDelay;
        uint32 AutoTriggerPeriod;
        uint32 ExposureTime;
        uint8 LEDSelect;
        uint8 Playing;
        uint8 Reserved[10];
    } LCR_PatternSeqSetting_t;

    typedef struct
    {
        uint16 ResolutionX;
        uint16 ResolutionY;
        uint16 FirstPix;
        uint16 FirstLine;
        uint16 ActiveWidth;
        uint16 ActiveHeight;
        uint8 Reserved[12];
    } LCR_VideoSetting_t;

    typedef struct
    {
        uint8 FrameRate;
        uint8 BitDepth;
        uint8 RGB;
    } LCR_VideoModeSetting_t;

    typedef struct
    {
        uint8 Rotate;
        uint8 LongAxisFlip;
        uint8 ShortAxisFlip;
        uint8 Reserved[11];
    } LCR_DisplaySetting_t;

    typedef struct
    {
        uint16 Red;
        uint16 Green;
        uint16 Blue;
    } LCR_LEDCurrent_t;

    typedef struct
    {
        uint8 Enable;
        uint8 Source;
        uint8 Polarity;
        uint32 Delay;
        uint32 PulseWidth;
        uint8 Reserved[12];
    } LCR_CamTriggerSetting_t;

    typedef struct
    {
        LCR_DisplayMode_t DisplayMode;
        LCR_DisplaySetting_t Display;
        LCR_LEDCurrent_t LEDCurrent;
        LCR_TestPattern_t TestPattern;
        LCR_VideoSetting_t Video;
        LCR_PatternSeqSetting_t PatternSeq;
        LCR_CamTriggerSetting_t CamTrigger;
        LCR_VideoModeSetting_t VideoMode;
        uint32 StaticColor;
        uint8 Reserved[32];
    } LCR_Setting_t;


    ErrorCode_t LCR_CMD_Open(void);
    ErrorCode_t LCR_CMD_Close(void);

    ErrorCode_t LCR_CMD_GetRevision(LCR_Revision_t Which, char *VersionStr);

    ErrorCode_t LCR_CMD_SetDisplayMode(LCR_DisplayMode_t Mode);
    LCR_DisplayMode_t LCR_CMD_GetDisplayMode(void);

    ErrorCode_t LCR_CMD_SetPowerMode(LCR_PowerMode_t Mode);
    LCR_PowerMode_t LCR_CMD_GetPowerMode(void);

    ErrorCode_t LCR_CMD_SetTestPattern(LCR_TestPattern_t TestPtn);
    LCR_TestPattern_t LCR_CMD_GetTestPattern(void);

    ErrorCode_t LCR_CMD_SetLEDCurrent(LCR_LEDCurrent_t *LEDSetting);
    ErrorCode_t LCR_CMD_GetLEDCurrent(LCR_LEDCurrent_t *LEDSetting);

    ErrorCode_t LCR_CMD_DisplayStaticImage(char const *fileNameWithPath);

    ErrorCode_t LCR_CMD_DisplayStaticColor(uint32 Color);

    ErrorCode_t LCR_CMD_SetDisplaySetting(LCR_DisplaySetting_t const *Setting);
    ErrorCode_t LCR_CMD_GetDisplaySetting(LCR_DisplaySetting_t *Setting);

    ErrorCode_t LCR_CMD_SetVideoSetting(LCR_VideoSetting_t const *Setting);
    ErrorCode_t LCR_CMD_GetVideoSetting(LCR_VideoSetting_t *Setting);

    ErrorCode_t LCR_CMD_SetVideoMode(LCR_VideoModeSetting_t *Setting);
    ErrorCode_t LCR_CMD_GetVideoMode(LCR_VideoModeSetting_t *Setting);

    ErrorCode_t LCR_CMD_SetInterleavePatternOrder(uint8 NumPatterns, uint8 const *PatternOrder);
    ErrorCode_t LCR_CMD_GetInterleavePatternOrder(uint8 *NumPatterns, uint8 *PatternOrder);

    ErrorCode_t LCR_CMD_SetPatternSeqSetting(LCR_PatternSeqSetting_t const *Setting);
    ErrorCode_t LCR_CMD_GetPatternSeqSetting(LCR_PatternSeqSetting_t *Setting);

    ErrorCode_t LCR_CMD_DefinePatternBMP(LCR_PatternCount_t PatternNum, char const *fileNameWithPath);
    //ErrorCode_t LCR_CMD_DefinePatternPix(LCR_PatternCount_t PatternNum, uint32 X, uint32 Y,
    //														uint8 *Data, uint32 Count);
    ErrorCode_t LCR_CMD_ReadPattern(LCR_PatternCount_t PatternNum, char *fileName);

    ErrorCode_t LCR_CMD_StartPatternSeq(uint8 Start);

    ErrorCode_t LCR_CMD_AdvancePatternSeq(void);

    ErrorCode_t LCR_CMD_GetCamTriggerSetting(LCR_CamTriggerSetting_t *Setting);
    ErrorCode_t LCR_CMD_SetCamTriggerSetting(LCR_CamTriggerSetting_t *Setting);

    //ErrorCode_t LCR_CMD_DisplayPattern(BOOL Enable, LCR_PatternCount_t PtnNumber);
    //
    //ErrorCode_t LCR_CMD_CaptureImage(Image_t *Image, LCR_CaptureMode_t Mode);
    //
    ErrorCode_t LCR_CMD_SaveSolution(char *SolutionName);
    ErrorCode_t LCR_CMD_GetSolutionNames(uint8 *Count, uint8 *DefaultSolution, char *SolutionName);

    ErrorCode_t LCR_CMD_ManageSolution(LCR_SolutionCommand_t Cmd, char *SolutionName);

#ifdef __cplusplus
}
#endif

#endif /* LCR_CMD_H_ */
