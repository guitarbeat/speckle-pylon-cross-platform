#include "SCVideoWriter.h"
#include "speckle_processing.h"

SCVideoWriter::SCVideoWriter()
{
    int junk=0;

}
/*****************************************************************/
void SCVideoWriter::SetOutputFile(QString base_fname)
{
    fname = base_fname+".avi";
}
/*****************************************************************/
//void SCVideoWriter::WriteOneFrame(CImg<unsigned char> img)
void SCVideoWriter::WriteOneFrame(int frame_number)
{
    //int height = img.height();
    //int width = img.width();

    //Mat frame(height, width, CV_8UC3);
    //CImg_to_OpenCVMat(&img, &frame);

    //if(!video.isOpened()) // CV_FOURCC('m','p','4','v')
    //    video.open(fname.toUtf8().constData(),CV_FOURCC('M','J','P','G') ,10, Size(width,height));
    //qDebug() << "writing one frame of "<< width << "x" <<height << " video.isOpened()= " <<video.isOpened() <<"fname=" << fname << endl;

    //video.write(frame);
}
/*****************************************************************/
void SCVideoWriter::CloseOutputFile(void)
{
    if(video.isOpened())
        video.release();
}
/*****************************************************************/
SCVideoWriter::~SCVideoWriter(void)
{
    CloseOutputFile();
}
/*****************************************************************/
