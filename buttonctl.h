#ifndef BUTTONCTL_H
#define BUTTONCTL_H

#include <QObject>
#include <QThread>
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

class ButtonCtl : public QThread
{
    Q_OBJECT
public:
    explicit ButtonCtl(QObject *parent = nullptr);
    ~ButtonCtl();
    void run();
private:
    int keys_fd;
    char ret[2];
    struct input_event t;

signals:
    void AButton();//172
    void BButton();//158
    void CButton();//116
    void DButton();//115
    void EButton();//114

};

#endif // BUTTONCTL_H
