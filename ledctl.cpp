#include "ledctl.h"

LedCtl::LedCtl(QObject *parent)
    : QObject{parent}
{
}

int LedCtl::led_open(QString DevName)
{
    this->fd=open(DevName.toUtf8().data(),O_RDWR);
    if(this->fd==-1)
    {
        qDebug()<<"LED Error!";
        return -1;
    }
}

void LedCtl::led_close()
{
    close(this->fd);
}

void LedCtl::led_off()
{
    ioctl(fd,LED_OFF);
}

void LedCtl::led_on()
{
    ioctl(fd,LED_ON);
}



