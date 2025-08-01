#ifndef CAMERADESCRIPTION_H
#define CAMERADESCRIPTION_H

#include <QObject>

class cameraDescription
{
public:
    explicit cameraDescription(void);
    QString description;
    int local_index; // index of specific camera type
    int camera_type;
};

#endif // CAMERADESCRIPTION_H
