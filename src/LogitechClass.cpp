#include "LogitechClass.h"
#include "speckle.h"
#include "camera.h"

extern SpeckleClass *speckle;

LogitechClass::LogitechClass(QObject *parent) :
    QObject(parent)
{
    //int junk=0;
}

/*****************************************************************************
 * Raw mode enabling/disabling tool for Logitech QuickCam devices
 *
 * Copyright 2007-2008 (c) Logitech. All Rights Reserved.
 *
 * This code and information is provided "as is" without warranty of
 * any kind, either expressed or implied, including but not limited to
 * the implied warranties of merchantability and/or fitness for a
 * particular purpose.
 *
 * Version: 1.0
 ****************************************************************************/

/*
 * Find a node in a given KS filter by GUID
 */
HRESULT LogitechClass::find_xu_node(IKsTopologyInfo *pKsTopologyInfo, GUID guid, DWORD *node)
{
    HRESULT hr = E_FAIL;
    DWORD dwNumNodes = 0;
    GUID guidNodeType;
    IKsControl *pKsControl = NULL;
    ULONG ulBytesReturned = 0;
    KSP_NODE ExtensionProp;

    if(!pKsTopologyInfo || !node)
        return E_POINTER;

    // Retrieve the number of nodes in the filter
    hr = pKsTopologyInfo->get_NumNodes(&dwNumNodes);
    if(!SUCCEEDED(hr))
        return hr;
    if(dwNumNodes == 0)
        return E_FAIL;

    // Find the extension unit node that corresponds to the given GUID
    for(unsigned int i = 0; i < dwNumNodes; i++)
    {
        hr = E_FAIL;
        pKsTopologyInfo->get_NodeType(i, &guidNodeType);
        if(IsEqualGUID(guidNodeType, KSNODETYPE_DEV_SPECIFIC))
        {
            hr = pKsTopologyInfo->CreateNodeInstance(i, IID_IKsControl, (void **)&pKsControl);
            if(SUCCEEDED(hr))
            {
                ExtensionProp.Property.Set = guid;
                ExtensionProp.Property.Id = 0;
                ExtensionProp.Property.Flags = KSPROPERTY_TYPE_SETSUPPORT | KSPROPERTY_TYPE_TOPOLOGY;
                ExtensionProp.NodeId = i;
                ExtensionProp.Reserved = 0;

                hr = pKsControl->KsProperty((PKSPROPERTY)&ExtensionProp, sizeof(ExtensionProp), NULL, 0, &ulBytesReturned);
                pKsControl->Release();
                if(SUCCEEDED(hr))
                {
                    *node = i;
                    break;
                }
            }
        }
    }

    return hr;
}


/*
 * Open a handle to the extension unit identified by the given GUID
 */
HRESULT LogitechClass::open_xu(IBaseFilter *pBaseFilter, GUID guid, XUHandle *xuHandle)
{
    HRESULT hr = E_FAIL;
    IKsTopologyInfo *pKsTopologyInfo = NULL;
    DWORD dwNode;
    IKsControl *pKsControl;

    if(!pBaseFilter || !xuHandle)
        return E_POINTER;

    hr = pBaseFilter->QueryInterface(__uuidof(IKsTopologyInfo), (void **)&pKsTopologyInfo);
    if(SUCCEEDED(hr))
    {
        hr = find_xu_node(pKsTopologyInfo, guid, &dwNode);
        if(SUCCEEDED(hr))
        {
            hr = pKsTopologyInfo->CreateNodeInstance(dwNode, IID_IKsControl, (void **)&pKsControl);
            if(SUCCEEDED(hr))
            {
                xuHandle->guid = guid;
                xuHandle->node = dwNode;
                xuHandle->pKsControl = pKsControl;
            }
        }
    }

    pKsTopologyInfo->Release();
    return hr;
}


/*
 * Close an extension unit handle
 */
void LogitechClass::close_xu(XUHandle *xuHandle)
{
    xuHandle->pKsControl->Release();
    xuHandle->pKsControl = NULL;
}


/*
 * Set an extension unit control
 */
HRESULT LogitechClass::set_xu_property(XUHandle *xuHandle, ULONG propertyID, ULONG size, BYTE *value)
{
    HRESULT hr = E_FAIL;
    KSP_NODE ExtensionProp;
    ULONG ulBytesReturned = 0;

    if(!xuHandle)
        return E_POINTER;
    if(!xuHandle->pKsControl)
        return E_HANDLE;

    ExtensionProp.Property.Set = xuHandle->guid;
    ExtensionProp.Property.Id = propertyID;
    ExtensionProp.Property.Flags = KSPROPERTY_TYPE_SET | KSPROPERTY_TYPE_TOPOLOGY;
    ExtensionProp.NodeId = xuHandle->node;

    hr = xuHandle->pKsControl->KsProperty(
        (PKSPROPERTY)&ExtensionProp,
        sizeof(ExtensionProp),
        (PVOID)value,
        size,
        &ulBytesReturned
    );

    return hr;
}


/*
 * Get the value of an extension unit control
 */
HRESULT LogitechClass::get_xu_property(XUHandle *xuHandle, ULONG propertyID, ULONG size, BYTE *value)
{
    HRESULT hr = E_FAIL;
    KSP_NODE ExtensionProp;
    ULONG ulBytesReturned = 0;

    if(!xuHandle)
        return E_POINTER;
    if(!xuHandle->pKsControl)
        return E_HANDLE;

    ExtensionProp.Property.Set = xuHandle->guid;
    ExtensionProp.Property.Id = propertyID;
    ExtensionProp.Property.Flags = KSPROPERTY_TYPE_GET | KSPROPERTY_TYPE_TOPOLOGY;
    ExtensionProp.NodeId = xuHandle->node;

    hr = xuHandle->pKsControl->KsProperty(
        (PKSPROPERTY)&ExtensionProp,
        sizeof(ExtensionProp),
        (PVOID)value,
        size,
        &ulBytesReturned
    );
    if(ulBytesReturned != size)
        hr = E_FAIL;

    return hr;
}


HRESULT LogitechClass::set_bayer_mode(IBaseFilter *pBaseFilter, bool bayer, unsigned int bpp)
{
    HRESULT hr = E_FAIL;
    XUHandle xuHandle;

    // Argument checking
    if(!pBaseFilter)
        return E_POINTER;
    if(bayer && (bpp != 8 && bpp != 10))
        return E_INVALIDARG;

    // Open the extension unit
    memset(&xuHandle, 0, sizeof(xuHandle));
    hr = open_xu(pBaseFilter, PROPSETID_LOGITECH_VIDEO_XU, &xuHandle);
    if(SUCCEEDED(hr))
    {
        // Enable or disable color processing
        BYTE value = bayer ? 1 : 0;
        hr = set_xu_property(&xuHandle, LXU_COLOR_PROCESSING_DISABLE_CONTROL, sizeof(value), &value);
        if(!SUCCEEDED(hr))
        {
            //fprintf(stderr, "ERROR: Unable to set LXU_COLOR_PROCESSING_DISABLE_CONTROL. (Error 0x%08X)\n", hr);
            //emit postSpeckleMessage(QString("ERROR: Unable to set LXU_COLOR_PROCESSING_DISABLE_CONTROL. (Error 0x%1).").arg(hr));
            qDebug() << "ERROR: Unable to set LXU_COLOR_PROCESSING_DISABLE_CONTROL. (Error 0x" << hr  << ").";
        }
        else
        {
            // Set the bits per pixel if bayer mode was successfully enabled
            if(bayer)
            {
                switch(bpp)
                {
                    case 10:
                        value = 1;
                        break;
                    case 8:
                    default:
                        value = 0;
                        break;
                }

                hr = set_xu_property(&xuHandle, LXU_RAW_DATA_BIT_PER_PIXEL_CONTROL, sizeof(value), &value);
                if(!SUCCEEDED(hr))
                {
                    //fprintf(stderr, "ERROR: Unable to set LXU_RAW_DATA_BIT_PER_PIXEL_CONTROL. (Error 0x%08X)\n", hr);
                    //emit postSpeckleMessage(QString("ERROR: Unable to set LXU_RAW_DATA_BIT_PER_PIXEL_CONTROL. (Error 0x%1).").arg(hr));
                    qDebug() << "ERROR: Unable to set LXU_RAW_DATA_BIT_PER_PIXEL_CONTROL. (Error 0x" << hr  << ").";
                }
            }
        }
        close_xu(&xuHandle);
    }
    else
    {
        //fprintf(stderr, "ERROR: Unable to open PROPSETID_LOGITECH_VIDEO_XU. (Error 0x%08X)\n", hr);
        emit postSpeckleMessage(QString("ERROR: Unable to open PROPSETID_LOGITECH_VIDEO_XU. (Error 0x%1).").arg(hr));
        qDebug() << "ERROR: Unable to open PROPSETID_LOGITECH_VIDEO_XU. (Error 0x" << hr  << ").";
    }
    return hr;
}


HRESULT LogitechClass::get_bayer_mode(IBaseFilter *pBaseFilter, bool *bayer, unsigned int *bpp)
{
    HRESULT hr = E_FAIL;
    XUHandle xuHandle;

    // Argument checking
    if(!pBaseFilter)
        return E_POINTER;

    // Open the extension unit
    memset(&xuHandle, 0, sizeof(xuHandle));
    hr = open_xu(pBaseFilter, PROPSETID_LOGITECH_VIDEO_XU, &xuHandle);
    if(SUCCEEDED(hr))
    {
        // Check if color processing is enabled
        BYTE value = 0xFF;
        hr = get_xu_property(&xuHandle, LXU_COLOR_PROCESSING_DISABLE_CONTROL, sizeof(value), &value);
        if(!SUCCEEDED(hr))
        {
            //fprintf(stderr, "ERROR: Unable to get LXU_COLOR_PROCESSING_DISABLE_CONTROL. (Error 0x%08X)\n", hr);
            //emit postSpeckleMessage(QString("ERROR: Unable to get LXU_COLOR_PROCESSING_DISABLE_CONTROL. (Error 0x%1).").arg(hr));
            qDebug() << "ERROR: Unable to get LXU_COLOR_PROCESSING_DISABLE_CONTROL. (Error 0x" << hr << ").";
        }
        else
        {
            if(bayer)
            {
                *bayer = (value == 1);	// LXU_COLOR_PROCESSING_DISABLE_CONTROL == 1 means Bayer mode is enabled
            }

            if(bpp != NULL && bayer != false)
            {
                value = 0xFF;
                hr = get_xu_property(&xuHandle, LXU_RAW_DATA_BIT_PER_PIXEL_CONTROL, sizeof(value), &value);
                if(!SUCCEEDED(hr))
                {
                    //fprintf(stderr, "ERROR: Unable to get LXU_RAW_DATA_BIT_PER_PIXEL_CONTROL. (Error 0x%08X)\n", hr);
                    //emit postSpeckleMessage(QString("ERROR: Unable to get LXU_RAW_DATA_BIT_PER_PIXEL_CONTROL. (Error 0x%1).").arg(hr));
                    qDebug() << "ERROR: Unable to get LXU_RAW_DATA_BIT_PER_PIXEL_CONTROL. (Error 0x" << hr << ").";
                }
                else
                {
                    switch(value)
                    {
                        case 0:
                            *bpp = 8;
                            break;
                        case 1:
                            *bpp = 10;
                            break;
                        default:
                            hr = E_NOTIMPL;
                    }
                }
            }
        }

        close_xu(&xuHandle);
    }
    else
    {
        //fprintf(stderr, "ERROR: Unable to open PROPSETID_LOGITECH_VIDEO_XU. (Error 0x%08X)\n", hr);
        //emit postSpeckleMessage(QString("ERROR: Unable to open PROPSETID_LOGITECH_VIDEO_XU. (Error 0x%1).").arg(hr));
        qDebug() << "ERROR: Unable to open PROPSETID_LOGITECH_VIDEO_XU. (Error 0x" << hr << ").";
    }
    return hr;
}


/*
 * Set bayer mode according to the command line options
 */
void LogitechClass::process_filter(IBaseFilter *pBaseFilter)
{
    HRESULT hr = E_FAIL;

    if(g_Args.Set)
    {
        hr = set_bayer_mode(pBaseFilter, g_Args.Bayer, g_Args.Bpp);
        if(SUCCEEDED(hr))
        {
            if(g_Args.Bayer)
            {
                //printf("    Bayer mode successfully enabled (%u bits).\n", g_Args.Bpp);
                emit postSpeckleMessage(QString("Bayer mode successfully enabled (%1 bits).").arg(g_Args.Bpp));\
                qDebug() << "    Bayer mode successfully enabled (" << g_Args.Bpp << " bits).";
            }
            else
            {
                //printf("    Bayer mode successfully disabled.\n");
                emit postSpeckleMessage(QString("Bayer mode successfully disabled."));
                qDebug() << "    Bayer mode successfully disabled.";
            }
        }
        else
        {
            //fprintf(stderr, "ERROR: Unable to set Bayer mode.\n");
            emit postSpeckleMessage(QString("ERROR: Unable to set Bayer mode."));
            qDebug() << "    ERROR: Unable to set Bayer mode.";
        }
    }
    else
    {
        bool bayer = false;
        unsigned int bpp = 0xFF;
        hr = get_bayer_mode(pBaseFilter, &bayer, &bpp);
        if(SUCCEEDED(hr))
        {
            if(bayer)
            {
                //printf("Current status: Bayer mode enabled (%u bits).\n", bpp);
                emit postSpeckleMessage(QString("Current status: Bayer mode enabled (%1 bits).").arg(bpp));
            }
            else
            {
                //printf("Current status: Bayer mode disabled.\n");
                emit postSpeckleMessage(QString("Current status: Bayer mode disabled."));
            }
        }
        else
        {
            //fprintf(stderr, "ERROR: Unable to determine current status.\n");
            emit postSpeckleMessage(QString("ERROR: Unable to determine current status."));
        }
    }
}


/*
 * Enumerate all video devices
 *
 * See also:
 *
 * Using the System Device Enumerator:
 *     http://msdn2.microsoft.com/en-us/library/ms787871.aspx
 */
HRESULT LogitechClass::enum_devices()
{
    HRESULT hr;

    //printf("Enumerating video input devices ...\n");
    //emit postSpeckleMessage(QString("Enumerating video input devices ..."));
    qDebug() << "Enumerating video input devices ...";

    // Create the System Device Enumerator.
    ICreateDevEnum *pSysDevEnum = NULL;
    hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
        IID_ICreateDevEnum, (void **)&pSysDevEnum);
    if(FAILED(hr))
    {
        //fprintf(stderr, "ERROR: Unable to create system device enumerator.\n");
        emit postSpeckleMessage(QString("ERROR: Unable to create system device enumerator."));
        return hr;
    }

    // Obtain a class enumerator for the video input device category.
    IEnumMoniker *pEnumCat = NULL;
    hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnumCat, 0);

    if(hr == S_OK)
    {
        // Enumerate the monikers.
        IMoniker *pMoniker = NULL;
        ULONG cFetched;
        while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
        {
            IPropertyBag *pPropBag;
            hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
                (void **)&pPropBag);
            if(SUCCEEDED(hr))
            {
                // To retrieve the filter's friendly name, do the following:
                VARIANT varName;
                VariantInit(&varName);
                hr = pPropBag->Read(L"FriendlyName", &varName, 0);
                if (SUCCEEDED(hr))
                {
                    VARIANT varPath;
                    VariantInit(&varPath);
                    hr = pPropBag->Read(L"DevicePath", &varPath, 0);
                    QString bayer_cam_name = QString::fromWCharArray(varName.bstrVal);
                    QString bayer_cam_path = QString::fromWCharArray(varPath.bstrVal);
                    //int camera_compare = QString::compare(bayer_cam_name, speckle->theCamera.camera_description, Qt::CaseInsensitive);
                    if (SUCCEEDED(hr) && speckle->theCamera.camera_description.contains(bayer_cam_name, Qt::CaseInsensitive))
                    {
                        //wprintf(L"  Found device: %s [%s]\n", varName.bstrVal, varPath.bstrVal);

                        emit postSpeckleMessage(QString("Found Device: %1").arg(bayer_cam_name));
                        qDebug() << "Found Device: " << bayer_cam_name << "[" << bayer_cam_path << "]";
                    }
                    else
                    {
                        //wprintf(L"  Found device: %s\n", varName.bstrVal);
                        //emit postSpeckleMessage(QString("Found Device: %1").arg(string_test1));
                        qDebug() << "Found Device: " << bayer_cam_name;
                        qDebug() << "    Not updating bayer mode -> this is not the current camera";
                    }
                    VariantClear(&varPath);
                }
                VariantClear(&varName);

                // To create an instance of the filter, do the following:
                IBaseFilter *pFilter;
                hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter,
                    (void**)&pFilter);

                if(SUCCEEDED(hr))
                    if(SUCCEEDED(hr))
                        process_filter(pFilter);

                // Remember to release pFilter later.
                pPropBag->Release();
            }
            pMoniker->Release();
        }
        pEnumCat->Release();
    }
    pSysDevEnum->Release();

    return 0;
}

/*
void LogitechClass::print_usage(void)
{
    emit postSpeckleMessage(QString("enable: 1 to enable Bayer mode, 0 to disable it"));
    emit postSpeckleMessage(QString("bpp:    bits per pixel (currently only 8 and 10 are supported, default is 8)"));
    /*
    printf(
        "Usage: %S [enable [bpp]]\n"
        "  enable: 1 to enable Bayer mode, 0 to disable it\n"
        "  bpp:    bits per pixel (currently only 8 and 10 are supported, default is 8)\n",
        argv0
    );

    return 1;
}
*/
/*
void LogitechClass::show_bayer_help(void)
{
    emit postSpeckleMessage(QString("enable: 1 to enable Bayer mode, 0 to disable it"));
    emit postSpeckleMessage(QString("bpp:    bits per pixel (currently only 8 and 10 are supported, default is 8)"));
}

int LogitechClass::show_current_bayer_value(void)
{
    int result;

    g_Args.Set = false;

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    result = enum_devices();

    CoUninitialize();

    return result;
}
*/
int LogitechClass::update_bayer_mode(bool bayer_setting)
{
    int result;
    g_Args.Set = true;
    g_Args.Bayer = bayer_setting;
    g_Args.Bpp = 8;
    /*g_Args.Bpp = argc == 2 ? 8 : _wtoi(argv[2]);
    if(g_Args.Bpp != 8 && g_Args.Bpp != 10)
    {
        emit postSpeckleMessage(QString("ERROR: Unsupported value specified for bits per pixel."));
        //fprintf(stderr, "ERROR: Unsupported value specified for bits per pixel.\n");
        return print_usage(argv[0]);
    }
    */
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    result = enum_devices();

    CoUninitialize();

    return result;
}
