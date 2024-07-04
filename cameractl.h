#ifndef CAMERACTL_H
#define CAMERACTL_H

#include <QObject>
#include <QThread>
#include <QMainWindow>
#include <QDebug>
#include <QPixmap>
#include <QTimer>
#include <QDateTime>
#include <QPainter>
#include <QMessageBox>
#include <QElapsedTimer>
#include "videodevice.h"
inline void yuyv422_to_rgb888(unsigned char *yuyvdata, unsigned char *rgbdata, int w, int h);
class CameraCtl : public QThread
{
    Q_OBJECT
public:
    explicit CameraCtl(QObject *parent = nullptr);
    ~CameraCtl();
    void run();
    void init();

private:
    VideoDevice*cam;
    int w,h,bpp;
    QString fmt;
    unsigned char * cam_raw_data,*cam_rgb_data;
    size_t frame_len;
    QImage img;
    QPixmap pix;
    bool pass,isOpen;
    quint64 framenum;
    int beginTime;
    QElapsedTimer elapsedTimer;

signals:
    void getFrameQPixmap(QPixmap);

};

#endif // CAMERACTL_H
