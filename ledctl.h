#ifndef LEDCTL_H
#define LEDCTL_H

#include <QObject>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <QDebug>
#define   LED_ON  1
#define   LED_OFF 0
class LedCtl : public QObject
{
    Q_OBJECT
public:
    explicit LedCtl(QObject *parent = nullptr);
    int led_open(QString);
    void led_close();
    void led_off();
    void led_on();
private:
    int fd;
};

#endif // LEDCTL_H
