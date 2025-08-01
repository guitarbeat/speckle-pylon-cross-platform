#ifndef SPECKLEDISPLAY_H
#define SPECKLEDISPLAY_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QActionGroup>
#include <QTimer>


class SpeckleDisplay : public QGraphicsView
{
    Q_OBJECT

public:
    SpeckleDisplay(QWidget *parent=nullptr);
    enum {RAW_IMG, SC_IMG, OVERLAY_IMG, VIDEO_IN_IMG, NO_IMG};
    enum {FIT, NO_FIT};

    void setImgSrc(int src);
    int getImgSrc(void) { return image_to_show; }

signals:
    void scCtrlPointsChanged(QPolygonF polygon);
    void videoCtrlPointsChanged(QPolygonF polygon);
    void roiAdded(QPolygonF polygon, QColor color);
    void allROIVisibilityToggled(bool show);
    void cameraAOISelected(QRectF rect);
    void toggleHideOverlay(void);
    void incrementSCmin(float);
    void incrementSCmax(float);
    void incrementExposure(float);

public slots:
    void updateRaw(QPixmap *, int fps);
    void updateSC(QPixmap *, int fps);
    void updateOverlay(QPixmap *, int fps);
    void updateVideoIn(QPixmap *, int fps);
    void srcImgChanged(QAction *action);
    void toggleFitMode(bool checked);
    void isLive(bool status);
    void toggleFPSOverlay(bool status);
    void updateInfo(int type, QString text);
    void exportImage(void);
    void popoutWindow(void);
    void addROI(void);
    void removeROI(int idx);
    void updateROIColor(int idx, QColor color);
    void setROIVisibility(int idx, bool is_visible);
    void toggleShowROICheck(bool checked);
    void setSCCtrlPoints(QPolygonF polygon);
    void setVideoCtrlPoints(QPolygonF polygon);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    QGraphicsScene *scene;
    QPixmap pixmap;
    QGraphicsPixmapItem *pixmapItem;

    QGraphicsView *popout;

    int fit_mode;
    int image_to_show;
    QGraphicsSimpleTextItem *framerate, *info;
    QGraphicsSimpleTextItem *vertex_coords;
    bool is_live;
    bool show_fps;
    QTimer *info_timeout;

    QGraphicsPolygonItem *activePolygonItem;
    QList<QGraphicsPolygonItem *> roiPolygonItemList;
    QPolygonF controlPolygon;
    QGraphicsEllipseItem *vertices[3];
    int movingIdx; // index of point being moved
    QList<QColor> colors; // ROI Colors
    QList<QColor>::const_iterator next_color;

    // Flags to control mouse clicks and keyboard events
    bool polyAdd = false;
    bool showHelp = false;
    bool movePoint = false;
    bool ctrlPointSelection = false;
    bool showVertices = true;
    bool cameraAOISelection = false;

    // popup menu actions
    QMenu *srcMenu;
    QActionGroup *imageSrcGroup;
    QAction *scSrcAct, *rawSrcAct, *overlaySrcAct, *videoinSrcAct, *noneSrcAct;
    QAction *fitImgAct;
    QAction *exportAct;
    QAction *toggleROIs;
    QAction *popoutAct;

    void initROIColors(void);
    void updateDisplay(void);
    void updatePixmap(QPixmap *qp);
    void createActions(void);
    void addPolygonPoint(QMouseEvent *);
    void removePolygonPoint(QMouseEvent *);
    void movePolygonPoint(QMouseEvent *);
    void findClosestPointSegment(QPolygonF poly, QPointF curr_point, float *d_to_pt,
                                 float *d_to_seg, int *ipt, int *iseg);
    void addFramerateOverlay(void);
    void updateFramerate(int fps);
    void updateFrameratePosition(void);
    void addInfoOverlay(void);
    void updateInfoPosition(void);
    void addVertexCoordinateOverlay(void);
    void startNewROI(void);
    void finishNewROI(void);
    QPen getROIPen(QColor color);
    QBrush getROIBrush(QColor color);
    void startControlPoints(void);
    void finishControlPoints(void);
    void showPolyVertices(QPolygonF poly);
    void hidePolyVertices(void);
    void allROIVisibilityToggledtest(bool checked);
    void startCameraAOI(void);
    void finishCameraAOI(void);

    // Dynamic Light
    QPixmap DL_pixmap;
    QGraphicsPixmapItem *DL_pixmapItem;
    bool show_logo = false;
    void addLogo(void);
};

#endif // SPECKLEDISPLAY_H
