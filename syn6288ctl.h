#ifndef SYN6288CTL_H
#define SYN6288CTL_H

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
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <QTextCodec>
#include <errno.h>
class SYN6288Ctl : public QObject
{
    Q_OBJECT
public:
    explicit SYN6288Ctl(QObject *parent = nullptr);
    int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop);
    void SYN_FrameInfo(uint8_t Music, char *HZdata);
    char* UTF8ToGB2312(char *strUtf8);
public:
    int fd, nByte;
    QString uartDevice = "/dev/ttySAC0";
    char buffer[512];
};

#endif // SYN6288CTL_H
