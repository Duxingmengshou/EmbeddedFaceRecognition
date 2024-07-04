#include "cameractl.h"

CameraCtl::CameraCtl(QObject *parent)
    : QThread{parent}
{
    w=640,h=480,bpp=4;
    fmt="YUYV";
    cam_raw_data=(unsigned char*)malloc(w*h*bpp);
    cam_rgb_data=(unsigned char*)malloc(w*h*bpp);
    isOpen=0;
    init();
}

CameraCtl::~CameraCtl()
{
    delete cam;
    free(cam_raw_data);
    free(cam_rgb_data);
}

void CameraCtl::run()
{
    while(isOpen){
        cam->get_frame((void**)&cam_raw_data,&frame_len);
        yuyv422_to_rgb888(cam_raw_data,cam_rgb_data,w,h);
        img=QImage(cam_rgb_data,w,h,QImage::Format_RGB888);
        // 创建QPainter对象来绘制文本
        QPainter painter(&img);
        painter.setPen(Qt::blue); // 设置画笔颜色为白色
        painter.setFont(QFont("Arial", 24)); // 设置字体
        // 获取当前时间
        QString currentTime = QDateTime::currentDateTime().toString("hh:mm:ss");
        // 假设fps是你计算出的帧率
        double fps = framenum++/(0.001*elapsedTimer.elapsed()-beginTime); // 示例帧率值
        //        qDebug()<<elapsedTimer.elapsed();
        QString fpsText = QString("FPS: %1").arg(fps);
        // 绘制帧率和时间
        painter.drawText(10, 30, fpsText); // 在图像的左上角绘制帧率
        painter.drawText(10, 60, currentTime); // 在帧率下方绘制当前时间
        painter.end(); // 结束绘画
        pix = QPixmap::fromImage(img,Qt::AutoColor);
        emit this->getFrameQPixmap(pix);
        cam->unget_frame();
        QThread::msleep(30);
    }
}

void CameraCtl::init()
{
    if(!isOpen){
        isOpen=!isOpen;
        cam=new VideoDevice("/dev/video4");
        if(cam->open_device()==-1)
        {
            qDebug()<<"open error";
        }
        else
        {
            connect(cam,&VideoDevice::display_error,this,[this](QString msg){
                qDebug()<<"error "<<msg;
                cam->close_device();
            });
            cam->init_device(w,h,fmt);
            cam->start_capturing();
            cam->get_frame((void**)&cam_raw_data,&frame_len);
            yuyv422_to_rgb888(cam_raw_data,cam_rgb_data,w,h);
            img=QImage(cam_rgb_data,w,h,QImage::Format_RGB888);
            pix = QPixmap::fromImage(img,Qt::AutoColor);
            cam->unget_frame();
            pass=0;
            framenum=1;
            elapsedTimer.start();
            beginTime=elapsedTimer.elapsed();
        }
    }
    else{
        qDebug()<<"already open";
    }
}



















inline void yuyv422_to_rgb888(unsigned char *yuyvdata, unsigned char *rgbdata, int w, int h)
{
    //码流Y0 U0 Y1 V1 Y2 U2 Y3 V3 --》YUYV像素[Y0 U0 V1] [Y1 U0 V1] [Y2 U2 V3] [Y3 U2 V3]--》RGB像素
    int r1, g1, b1;
    int r2, g2, b2;
    int i;

    for(i=0; i<w*h/2; i++)
    {
        char data[4];
        memcpy(data, yuyvdata+i*4, 4);
        unsigned char Y0=data[0];
        unsigned char U0=data[1];
        unsigned char Y1=data[2];
        unsigned char V1=data[3];

        r1 = Y0+1.4075*(V1-128);
        if(r1>255) r1=255;
        if(r1<0)   r1=0;

        g1 =Y0- 0.3455 * (U0-128) - 0.7169*(V1-128);
        if(g1>255)  g1=255;
        if(g1<0)    g1=0;

        b1 = Y0 + 1.779 * (U0-128);
        if(b1>255)  b1=255;
        if(b1<0)    b1=0;

        r2 = Y1+1.4075*(V1-128);
        if(r2>255)  r2=255;
        if(r2<0)    r2=0;

        g2 = Y1- 0.3455 * (U0-128) - 0.7169*(V1-128);
        if(g2>255)    g2=255;
        if(g2<0)      g2=0;

        b2 = Y1 + 1.779 * (U0-128);
        if(b2>255)    b2=255;
        if(b2<0)      b2=0;

        rgbdata[i*6+0]=r1;
        rgbdata[i*6+1]=g1;
        rgbdata[i*6+2]=b1;
        rgbdata[i*6+3]=r2;
        rgbdata[i*6+4]=g2;
        rgbdata[i*6+5]=b2;
    }
}
