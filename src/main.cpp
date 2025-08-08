#include <QApplication>
#include <QMainWindow>
#include "speckle.h"
#include "specklewindow.h"

void parseCommandLine(QStringList args);

SpeckleClass *speckle;
SpeckleWindow *speckle_window;

/*****************************************************************************/
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    qDebug().noquote() << QString("Speckle Software v%1.%2.%3 (%4)")
                          .arg(3)
                          .arg(1)
                          .arg(1)
                          .arg(QDate::currentDate().toString(Qt::ISODate));

    QPixmap pixmap("://icons/splash.png");
//    QPixmap pixmap("://icons/DynamicLight.png");
	QSplashScreen splash(pixmap);
	splash.show();
	app.processEvents();       

#ifdef USE_PYLON
    // just do this once in main so multiple cameras can be opened without calling this repeatedly
    Pylon::PylonAutoInitTerm autoInitTerm;  // PylonInitialize() will be called now
#endif

    speckle = new SpeckleClass;
    //parseCommandLine(app.arguments());
    speckle_window = new SpeckleWindow;

    speckle_window->show();
	splash.finish(speckle_window);
    return app.exec();
}
/*****************************************************************************/
void parseCommandLine(QStringList args) {
	int idx;
    speckle->command_line = args.join(" ");
    speckle->theCamera->camera_specified = false;
    speckle->disable_daq = false;

    speckle->theCamera->camera_name = "cam0";

#ifdef USE_NIIMAQDX
    speckle->theCamera->camera_type = CAMERA_NIIMAQDX;
    speckle->theCamera->camera_name = args.at(1);
    speckle->theCamera->camera_specified = true;
#endif

#ifdef USE_NIIMAQ
    speckle->theCamera->camera_type = CAMERA_NI;
    speckle->theCamera->camera_name = args.at(1);
    speckle->theCamera->camera_specified = true;
#endif

#ifdef USE_PYLON
    speckle->theCamera->camera_type = CAMERA_PYLON;
    speckle->theCamera->camera_specified = true;
#endif

#ifdef USE_FRAMEGRABBER
    speckle->theCamera->camera_type = CAMERA_FRAMEGRABBER;
    speckle->theCamera->camera_specified = true;
#endif

#ifdef USE_THORLABS
    speckle->theCamera->camera_type = CAMERA_THORLABS;
    speckle->theCamera->camera_specified = true;
#endif

    if(args.indexOf("--simulated") > 0) {
        speckle->theCamera->camera_type = CAMERA_NONE;
        speckle->theCamera->camera_specified = true;
	}
    if((idx = args.indexOf("--pylon")) > 0) {
        speckle->theCamera->camera_type = CAMERA_PYLON;
        speckle->theCamera->camera_specified = true;
        if(args.length() - 1 > idx)
            speckle->theCamera->ip_address = args.at(idx+1);
    }
    if(args.indexOf("--nodaq") > 0) {
        speckle->disable_daq = true;
	}

}
/*****************************************************************************/
