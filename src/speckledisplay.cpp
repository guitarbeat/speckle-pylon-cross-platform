#include "speckledisplay.h"
#include <QtWidgets>
#include <QDebug>
#include <QMouseEvent>

/****************************************/
SpeckleDisplay::SpeckleDisplay(QWidget *parent)
    :QGraphicsView(parent)
{
    scene = new QGraphicsScene;
    scene->setBackgroundBrush(Qt::darkGray);

    pixmap = QPixmap(1024, 768); // Initialize to arbitrary size
    pixmapItem = new QGraphicsPixmapItem(pixmap);
    scene->addItem(pixmapItem);
    scene->setSceneRect(pixmap.rect());

    // Initialize object used for interactive editing of ROIs and control points
    activePolygonItem = new QGraphicsPolygonItem;
    activePolygonItem->setVisible(false);
    activePolygonItem->setZValue(1); // Always draw on top
    scene->addItem(activePolygonItem);
    initROIColors();

    // Initialize vertices for control point selection
    for(int i=0;i<3;i++)
    {
        vertices[i] = scene->addEllipse(100, 100, 30, 30); // Placeholder position
        vertices[i]->setVisible(false);
    }
    vertices[0]->setBrush(QBrush(Qt::red));
    vertices[1]->setBrush(QBrush(Qt::green));
    vertices[2]->setBrush(QBrush(Qt::blue));

    is_live = false;
    show_fps = true;
    addFramerateOverlay();
    addInfoOverlay();
    addVertexCoordinateOverlay();
    fit_mode = FIT;

    if(show_logo)
        addLogo();

    createActions();
    setScene(scene);
}
/****************************************/
void SpeckleDisplay::initROIColors(void)
{
    colors.append(Qt::red);
    colors.append(Qt::green);
    colors.append(Qt::blue);
    colors.append(Qt::cyan);
    colors.append(Qt::magenta);
    colors.append(Qt::yellow);
    colors.append(Qt::darkRed);
    colors.append(Qt::darkGreen);
    colors.append(Qt::darkBlue);
    colors.append(Qt::darkCyan);
    colors.append(Qt::darkMagenta);
    colors.append(Qt::darkYellow);
    colors.append(Qt::black);
    colors.append(Qt::gray);
    next_color = colors.constBegin();
}
/****************************************/
void SpeckleDisplay::setImgSrc(int src)
{
    image_to_show = src;
    scSrcAct->setChecked(image_to_show == SC_IMG);
    rawSrcAct->setChecked(image_to_show == RAW_IMG);
    overlaySrcAct->setChecked(image_to_show == OVERLAY_IMG);
    videoinSrcAct->setChecked(image_to_show == VIDEO_IN_IMG);
    noneSrcAct->setChecked(image_to_show == NO_IMG);
}
/****************************************/
void SpeckleDisplay::updateDisplay(void)
{
   if(fit_mode == FIT)
       fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

   updateFrameratePosition();
   updateInfoPosition();
}
/****************************************/
void SpeckleDisplay::updatePixmap(QPixmap *qp)
{
    pixmap = *qp;
    pixmapItem->setPixmap(pixmap);

    if(scene->sceneRect() != pixmap.rect())
        scene->setSceneRect(pixmap.rect());
}
/****************************************/
void SpeckleDisplay::updateRaw(QPixmap *qp, int fps)
{
    if(image_to_show == RAW_IMG)
    {
        updatePixmap(qp);
        updateFramerate(fps);
    }
}
/****************************************/
void SpeckleDisplay::updateSC(QPixmap *qp, int fps)
{
    if(image_to_show == SC_IMG)
    {
        updatePixmap(qp);
        updateFramerate(fps);
    }
}
/****************************************/
void SpeckleDisplay::updateOverlay(QPixmap *qp, int fps)
{
    if(image_to_show == OVERLAY_IMG)
    {
        updatePixmap(qp);
        updateFramerate(fps);
    }
}
/****************************************/
void SpeckleDisplay::updateVideoIn(QPixmap *qp, int fps)
{
    if(image_to_show == VIDEO_IN_IMG)
    {
        updatePixmap(qp);
        updateFramerate(fps);
    }
}
/****************************************/
void SpeckleDisplay::toggleFitMode(bool checked)
{
    if(checked)
        fit_mode = FIT;
    else
        fit_mode = NO_FIT;

    updateDisplay();
}
/****************************************/
void SpeckleDisplay::addPolygonPoint(QMouseEvent *event)
{
    const QPointF curr_point = mapToScene(event->pos());
    QPolygonF c_poly = activePolygonItem->polygon();

    float dmin_pt, dmin_seg;
    int i_pt, i_seg;

    findClosestPointSegment(c_poly, curr_point, &dmin_pt, &dmin_seg, &i_pt, &i_seg);

    if(dmin_pt>25 && !movePoint)
    {
        c_poly.insert(i_seg+1, mapToScene(event->pos()));
        activePolygonItem->setPolygon(c_poly);
    }
}
/****************************************/
void SpeckleDisplay::removePolygonPoint(QMouseEvent *event)
{
    const QPointF curr_point = mapToScene(event->pos());
    QPolygonF c_poly = activePolygonItem->polygon();

    float dmin_pt, dmin_seg;
    int i_pt, i_seg;

    findClosestPointSegment(c_poly, curr_point, &dmin_pt, &dmin_seg, &i_pt, &i_seg);
    if(c_poly.size() > 3 && dmin_pt < 100)
    {
        c_poly.removeAt(i_pt);
        activePolygonItem->setPolygon(c_poly);
    }
}
/****************************************/
void SpeckleDisplay::movePolygonPoint(QMouseEvent *event)
{
    const QPointF curr_point = mapToScene(event->pos());
    QPolygonF c_poly = activePolygonItem->polygon();

    float dmin_pt, dmin_seg;
    int i_pt, i_seg;

    if(!movePoint)
    {
        findClosestPointSegment(c_poly, curr_point, &dmin_pt, &dmin_seg, &i_pt, &i_seg);
        if(dmin_pt<25)
        {
            movePoint=true;
            movingIdx=i_pt;
        }
    }
    if(movePoint)
    {
        c_poly[movingIdx] = curr_point;
        activePolygonItem->setPolygon(c_poly);
        if(ctrlPointSelection)
            showPolyVertices(c_poly);

        // Draw vertex pixel coordinates
        QPoint coord = curr_point.toPoint();
        vertex_coords->setText(QString("(%1, %2)").arg(coord.x()).arg(coord.y()));
        vertex_coords->setPos(coord + QPoint(10, -25));

        if(ctrlPointSelection)
            vertex_coords->setBrush(vertices[movingIdx]->brush());
        else
            vertex_coords->setBrush(QBrush(*next_color));

        if(!vertex_coords->isVisible())
            vertex_coords->show();
    }
}
/****************************************/
void SpeckleDisplay::findClosestPointSegment(QPolygonF poly, QPointF curr_point,
                                             float *d_to_pt, float *d_to_seg,
                                             int *ipt, int *iseg)
{
    // identify closest point and closest segment
    float dmin_pt = 1e10f, dmin_seg = dmin_pt;
    int i_pt=0, i_seg=0;
    for(int i=0;i<poly.size();i++)
    {
        const QPointF p = poly[i];
        const QPointF p_next = poly[(i+1)%poly.size()];
        const QPointF p_mid = 0.5*(p+p_next);
        const float d_pt = QLineF(curr_point, p).length();
        const float d_seg = QLineF(curr_point, p_mid).length();
        if(d_pt<dmin_pt) {dmin_pt=d_pt; i_pt=i;}
        if(d_seg<dmin_seg) {dmin_seg=d_seg; i_seg=i;}
    }

    *d_to_pt = dmin_pt;
    *d_to_seg = dmin_seg;
    *ipt = i_pt;
    *iseg = i_seg;
}
/****************************************/
void SpeckleDisplay::mousePressEvent(QMouseEvent *event)
{
    if(polyAdd && event->button() == Qt::LeftButton && (!ctrlPointSelection))
        addPolygonPoint(event);
    if(polyAdd && event->button() == Qt::RightButton && (!ctrlPointSelection))
        removePolygonPoint(event);

    QGraphicsView::mousePressEvent(event);
}
/****************************************/
void SpeckleDisplay::resizeEvent(QResizeEvent *event)
{
    if(fit_mode == FIT)
        updateDisplay();
}
/****************************************/
void SpeckleDisplay::wheelEvent(QWheelEvent *event)
{
  if(event->angleDelta().y() > 0)
    scale(1.1, 1.1);
  else
    scale(0.9, 0.9);
}
/****************************************/
void SpeckleDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if(polyAdd)
        movePolygonPoint(event);

    QGraphicsView::mouseMoveEvent(event);
}
/****************************************/
void SpeckleDisplay::mouseReleaseEvent(QMouseEvent *event)
{
    if(movePoint)
    {
        movePoint=false;
        vertex_coords->hide();
    }

    QGraphicsView::mouseReleaseEvent(event);
}
/****************************************/
void SpeckleDisplay::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Up)
        scale(1.05,1.05);
    if(event->key()==Qt::Key_Down)
        scale(0.95,0.95);
    if(event->key()==Qt::Key_A && !ctrlPointSelection &&
       image_to_show == SC_IMG && toggleROIs->isChecked())
    {
        polyAdd=true;
        startNewROI();
    }
    if(event->key()==Qt::Key_C && !polyAdd &&
       (image_to_show == SC_IMG || image_to_show == OVERLAY_IMG || image_to_show == RAW_IMG))
    {
        polyAdd=true;
        ctrlPointSelection=true;
        startControlPoints();
    }
    if(event->key()==Qt::Key_R && !cameraAOISelection &&
       (image_to_show == SC_IMG || image_to_show == OVERLAY_IMG))
    {
        polyAdd=true;
        cameraAOISelection = true;
        startCameraAOI();
    }
    if(event->key()==Qt::Key_Escape && polyAdd)
    {
        polyAdd=false;
        ctrlPointSelection=false;
        activePolygonItem->setVisible(false);
        hidePolyVertices();
    }
    if((event->key()==Qt::Key_Enter || event->key()==Qt::Key_Return) && polyAdd)
    {
        polyAdd=false;
        activePolygonItem->setVisible(false);

        if(ctrlPointSelection)
        {
            ctrlPointSelection=false;
            finishControlPoints();
        }
        else if(cameraAOISelection)
        {
            cameraAOISelection=false;
            finishCameraAOI();
        }
        else
            finishNewROI();
    }

    if(event->key()==Qt::Key_O)
        emit toggleHideOverlay();

    // hot keys for display settings
    if(event->key()==Qt::Key_J)
        emit incrementSCmin(-0.01);
    if(event->key()==Qt::Key_K)
        emit incrementSCmin(0.01);
    if(event->key()==Qt::Key_N)
        emit incrementSCmax(-0.01);
    if(event->key()==Qt::Key_M)
        emit incrementSCmax(0.01);
    if(event->key()==Qt::Key_U)
        emit incrementExposure(-0.1);
    if(event->key()==Qt::Key_I)
        emit incrementExposure(0.1);
    QGraphicsView::keyPressEvent(event);
}
/****************************************/
void SpeckleDisplay::contextMenuEvent(QContextMenuEvent *event)
{
    if(polyAdd)
        return;

    QMenu menu(this);

    QMenu *imgSrcMenu = menu.addMenu(tr("Image"));
    imgSrcMenu->addAction(scSrcAct);
    imgSrcMenu->addAction(rawSrcAct);
    imgSrcMenu->addAction(overlaySrcAct);
    imgSrcMenu->addAction(videoinSrcAct);
    imgSrcMenu->addAction(noneSrcAct);

    QMenu *zoomMenu = menu.addMenu(tr("View"));
    zoomMenu->addAction(fitImgAct);
    zoomMenu->addAction(popoutAct);

    if(image_to_show == SC_IMG)
        menu.addAction(toggleROIs);

    menu.addAction(exportAct);

    menu.exec(event->globalPos());
}
/****************************************/
void SpeckleDisplay::createActions(void)
{
    scSrcAct = new QAction("Speckle Contrast", this);
    scSrcAct->setCheckable(true);
    rawSrcAct = new QAction("Raw", this);
    rawSrcAct->setCheckable(true);
    overlaySrcAct = new QAction("Overlay", this);
    overlaySrcAct->setCheckable(true);
    videoinSrcAct = new QAction("Video In", this);
    videoinSrcAct->setCheckable(true);
    noneSrcAct = new QAction("None", this);
    noneSrcAct->setCheckable(true);

    imageSrcGroup = new QActionGroup(this);
    imageSrcGroup->addAction(scSrcAct);
    imageSrcGroup->addAction(rawSrcAct);
    imageSrcGroup->addAction(overlaySrcAct);
    imageSrcGroup->addAction(videoinSrcAct);
    imageSrcGroup->addAction(noneSrcAct);
    connect(imageSrcGroup, &QActionGroup::triggered, this, &SpeckleDisplay::srcImgChanged);

    fitImgAct = new QAction("Fit Image", this);
    fitImgAct->setCheckable(true);
    fitImgAct->setChecked(true);
    connect(fitImgAct, &QAction::triggered, this, &SpeckleDisplay::toggleFitMode);

    popoutAct = new QAction("Open in Popup", this);
    connect(popoutAct, &QAction::triggered, this, &SpeckleDisplay::popoutWindow);

    toggleROIs = new QAction("Show ROIs", this);
    toggleROIs->setCheckable(true);
    toggleROIs->setChecked(true);
    connect(toggleROIs, &QAction::toggled, this, &SpeckleDisplay::allROIVisibilityToggled);

    exportAct = new QAction("Export as PNG", this);
    connect(exportAct, &QAction::triggered, this, &SpeckleDisplay::exportImage);
}
/****************************************/
void SpeckleDisplay::srcImgChanged(QAction *action)
{
    if(action == scSrcAct)
        image_to_show = SC_IMG;
    else if(action == rawSrcAct)
        image_to_show = RAW_IMG;
    else if(action == overlaySrcAct)
        image_to_show = OVERLAY_IMG;
    else if(action == videoinSrcAct)
        image_to_show = VIDEO_IN_IMG;
    else if(action == noneSrcAct)
    {
        image_to_show = NO_IMG;
        pixmap.fill(Qt::black);
        pixmapItem->setPixmap(pixmap);
    }

    framerate->setText("");

    // Only show ROIs when SC_IMG is shown
    for(int i = 0; i < roiPolygonItemList.length(); i++)
        roiPolygonItemList[i]->setVisible(image_to_show == SC_IMG);
}
/****************************************/
void SpeckleDisplay::isLive(bool status)
{
    is_live = status;
    framerate->setVisible(is_live && show_fps);
}
/****************************************/
void SpeckleDisplay::addFramerateOverlay(void)
{
    framerate = scene->addSimpleText("");
    framerate->hide();
    framerate->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    QFont font = framerate->font();
    font.setPointSize(12);
    framerate->setFont(font);
    QBrush brush(Qt::white);
    framerate->setBrush(brush);
}
/****************************************/
void SpeckleDisplay::updateFramerate(int fps)
{
    int len = framerate->text().length();
    framerate->setText(QString("%1 fps").arg(fps));
    if (len != framerate->text().length())
        updateFrameratePosition(); // Update position if number of digits change
}
/****************************************/
void SpeckleDisplay::updateFrameratePosition(void)
{
    double width, scale;
    width = framerate->boundingRect().width();
    scale = viewportTransform().m11();
    framerate->setPos(scene->width() - (width + 5)/scale, 5);
}
/****************************************/
void SpeckleDisplay::toggleFPSOverlay(bool status)
{
    show_fps = status;
    framerate->setVisible(show_fps && is_live);
}
/****************************************/
void SpeckleDisplay::addInfoOverlay(void)
{
    info = scene->addSimpleText("");
    info->hide();
    info->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    QFont font = info->font();
    font.setPointSize(12);
    info->setFont(font);
    QBrush brush(Qt::white);
    info->setBrush(brush);

    info_timeout = new QTimer(this);
    info_timeout->setSingleShot(true);
    connect(info_timeout, &QTimer::timeout, this, [=]()->void{
        info->setVisible(false);
    });
}
/****************************************/
void SpeckleDisplay::updateInfo(int type, QString text)
{
    if(type == image_to_show)
    {
        info->setVisible(true);
        int len = info->text().length();
        info->setText(text);
        if (len != info->text().length())
            updateInfoPosition();
        info_timeout->start(5000);
    }
}
/****************************************/
void SpeckleDisplay::updateInfoPosition(void)
{
    double width, scale;
    width = info->boundingRect().width();
    scale = viewportTransform().m11();
    info->setPos(scene->width() - (width + 5)/scale, 60);
}
/****************************************/
void SpeckleDisplay::addVertexCoordinateOverlay(void)
{
    vertex_coords = scene->addSimpleText("");
    vertex_coords->hide();
    vertex_coords->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    QFont font = vertex_coords->font();
    font.setPointSize(8);
    vertex_coords->setFont(font);
    vertex_coords->setZValue(1); // Force on top of all other items
}
/****************************************/
void SpeckleDisplay::showPolyVertices(QPolygonF poly)
{
    qreal marker_width = 15;
    for(int i = 0; i < 3; i++)
    {
        QPointF pt = poly[i];
        vertices[i]->setRect(pt.x() - marker_width/2, pt.y() - marker_width/2, marker_width, marker_width);
        vertices[i]->setVisible(true);
    }
}
/****************************************/
void SpeckleDisplay::hidePolyVertices(void)
{
    for(int i = 0; i < 3; i++)
        vertices[i]->setVisible(false);
}
/****************************************/
void SpeckleDisplay::startNewROI(void)
{
    QPolygonF square;
    square << QPointF(pixmap.width()/2 - pixmap.height()/4, pixmap.height()/4)
           << QPointF(pixmap.width()/2 + pixmap.height()/4, pixmap.height()/4)
           << QPointF(pixmap.width()/2 + pixmap.height()/4, pixmap.height()*3/4)
           << QPointF(pixmap.width()/2 - pixmap.height()/4, pixmap.height()*3/4);
    activePolygonItem->setPolygon(square);
    activePolygonItem->setPen(getROIPen(*next_color));
    activePolygonItem->setVisible(true);
}
/****************************************/
void SpeckleDisplay::startCameraAOI(void)
{
    QPolygonF square;
    square << QPointF(pixmap.width()/2 - pixmap.height()/4, pixmap.height()/4)
           << QPointF(pixmap.width()/2 + pixmap.height()/4, pixmap.height()/4)
           << QPointF(pixmap.width()/2 + pixmap.height()/4, pixmap.height()*3/4)
           << QPointF(pixmap.width()/2 - pixmap.height()/4, pixmap.height()*3/4);
    activePolygonItem->setPolygon(square);
    activePolygonItem->setPen(getROIPen(*next_color));
    activePolygonItem->setVisible(true);
}
/****************************************/
void SpeckleDisplay::finishNewROI(void)
{
    roiPolygonItemList.append(new QGraphicsPolygonItem);
    roiPolygonItemList.last()->setPolygon(activePolygonItem->polygon().toPolygon());
    roiPolygonItemList.last()->setPen(getROIPen(*next_color));
    roiPolygonItemList.last()->setBrush(getROIBrush(*next_color));
    scene->addItem(roiPolygonItemList.last());

    emit roiAdded(roiPolygonItemList.last()->polygon(), *next_color);

    // Advance to next color and restart iterator if necessary
    ++next_color;
    if(next_color == colors.constEnd())
        next_color = colors.constBegin();
}
/****************************************/
void SpeckleDisplay::addROI(void)
{
    if(!polyAdd && !ctrlPointSelection && image_to_show == SC_IMG)
    {
        polyAdd=true;
        startNewROI();
    }
}
/****************************************/
void SpeckleDisplay::removeROI(int idx)
{
    if(image_to_show == SC_IMG)
    {
        roiPolygonItemList[idx]->setVisible(false);
        roiPolygonItemList.removeAt(idx);
    }
}
/****************************************/
void SpeckleDisplay::updateROIColor(int idx, QColor color)
{
    if(image_to_show == SC_IMG)
    {
        roiPolygonItemList[idx]->setPen(getROIPen(color));
        roiPolygonItemList[idx]->setBrush(getROIBrush(color));
    }
}
/****************************************/
void SpeckleDisplay::setROIVisibility(int idx, bool is_visible)
{
    if(image_to_show == SC_IMG)
        roiPolygonItemList[idx]->setVisible(is_visible);
}
/****************************************/
void SpeckleDisplay::toggleShowROICheck(bool checked)
{
    if(image_to_show == SC_IMG)
    {
        const QSignalBlocker blocker(toggleROIs); // Temporarily prevent action signal from firing
        toggleROIs->setChecked(checked);
    }
}
/****************************************/
QPen SpeckleDisplay::getROIPen(QColor color)
{
    return QPen(color, 2);
}
/****************************************/
QBrush SpeckleDisplay::getROIBrush(QColor color)
{
    color.setAlphaF(0.2); // Add transparency
    QBrush brush(color);
    return brush;
}
/****************************************/
void SpeckleDisplay::startControlPoints(void)
{
    if(controlPolygon.isEmpty())
        controlPolygon << QPointF(pixmap.width()/2, pixmap.height()/4)
                       << QPointF(pixmap.width()/2 + pixmap.height()/4, pixmap.height()*3/4)
                       << QPointF(pixmap.width()/2 - pixmap.height()/4, pixmap.height()*3/4);
    activePolygonItem->setPolygon(controlPolygon);
    activePolygonItem->setPen(QPen(Qt::green));
    activePolygonItem->setVisible(true);
    showPolyVertices(controlPolygon);
}
/****************************************/
void SpeckleDisplay::finishControlPoints(void)
{
    hidePolyVertices();
    controlPolygon = activePolygonItem->polygon();

    if(image_to_show == SC_IMG || image_to_show == RAW_IMG)
        emit scCtrlPointsChanged(controlPolygon);

    if(image_to_show == OVERLAY_IMG)
        emit videoCtrlPointsChanged(controlPolygon);
}
/****************************************/
void SpeckleDisplay::finishCameraAOI(void)
{
    emit cameraAOISelected(activePolygonItem->polygon().boundingRect());
    qDebug() << "ROI = " << activePolygonItem->polygon().boundingRect();
}
/****************************************/
void SpeckleDisplay::setSCCtrlPoints(QPolygonF new_poly)
{
    if(image_to_show == SC_IMG)
        controlPolygon = new_poly;
}
/****************************************/
void SpeckleDisplay::setVideoCtrlPoints(QPolygonF new_poly)
{
    if(image_to_show == OVERLAY_IMG)
        controlPolygon = new_poly;
}
/****************************************/
void SpeckleDisplay::exportImage(void)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export Image (.png)"),
        NULL, tr("Image Files (*.png)"));

    if(fileName.isNull())
        return;

    // export scene rather than view to preserve original size
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene->render(&painter);
    image.save(fileName);
}
/****************************************/
void SpeckleDisplay::popoutWindow(void)
{
    popout = new QGraphicsView();
    popout->setScene(scene);

    QString title;
    if(image_to_show == SC_IMG)
        title = "Speckle Contrast";
    else if(image_to_show == RAW_IMG)
        title = "Raw";
    else if(image_to_show == OVERLAY_IMG)
        title = "Overlay";

    popout->setWindowTitle(title);
    popout->show();
}
/****************************************/
void SpeckleDisplay::addLogo(void)
{
    DL_pixmap = QPixmap("://icons/DynamicLight.png");
    DL_pixmapItem = new QGraphicsPixmapItem(DL_pixmap);
    scene->addItem(DL_pixmapItem);
    DL_pixmapItem->setOffset(scene->width() - DL_pixmap.width(),
                             scene->height() - DL_pixmap.height());
}
/****************************************/
