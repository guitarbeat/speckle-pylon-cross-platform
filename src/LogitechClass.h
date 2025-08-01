#ifndef LOGITECHCLASS_H
#define LOGITECHCLASS_H

#include <QObject>

#include <dshow.h>
#include <Ks.h>				// Required by KsMedia.h
#include <KsMedia.h>		// For KSPROPERTY_CAMERACONTROL_FLAGS_*
#include <vidcap.h>			// For IKsTopologyInfo
#include <ksproxy.h>		// For IKsControl

class LogitechClass : public QObject
{
    Q_OBJECT

public:
    explicit LogitechClass(QObject *parent = 0);
    bool bayer_setting;
    //void show_bayer_help(void);
    //int show_current_bayer_value(void);
    HRESULT enum_devices();
    int update_bayer_mode(bool bayer_setting);

signals:
    void postSpeckleMessage(QString);

private:
    struct XUHandle {
        GUID			guid;
        DWORD			node;
        IKsControl		*pKsControl;
    };

    // Video processing extension unit
    DEFINE_GUIDSTRUCT("63610682-5070-49AB-B8CC-B3855E8D2250", PROPSETID_LOGITECH_VIDEO_XU);
    #define PROPSETID_LOGITECH_VIDEO_XU DEFINE_GUIDNAMED(PROPSETID_LOGITECH_VIDEO_XU)

    // Control: Enable or disable the color processing pipeline within the camera
    #define LXU_COLOR_PROCESSING_DISABLE_CONTROL	0x05
    // Control: Specify the number of bits per pixel for raw data
    #define LXU_RAW_DATA_BIT_PER_PIXEL_CONTROL		0x08


    // Command line arguments
    struct CmdArgs {
        bool Set;
        bool Bayer;
        int  Bpp;
    };

    CmdArgs g_Args;
    //CmdArgs g_Args = { 0 };

    HRESULT find_xu_node(IKsTopologyInfo *pKsTopologyInfo, GUID guid, DWORD *node);
    HRESULT open_xu(IBaseFilter *pBaseFilter, GUID guid, XUHandle *xuHandle);
    void close_xu(XUHandle *xuHandle);
    HRESULT set_xu_property(XUHandle *xuHandle, ULONG propertyID, ULONG size, BYTE *value);
    HRESULT get_xu_property(XUHandle *xuHandle, ULONG propertyID, ULONG size, BYTE *value);
    HRESULT set_bayer_mode(IBaseFilter *pBaseFilter, bool bayer, unsigned int bpp);
    HRESULT get_bayer_mode(IBaseFilter *pBaseFilter, bool *bayer, unsigned int *bpp);
    void process_filter(IBaseFilter *pBaseFilter); 
};

#endif // LOGITECHCLASS_H
