#include "syn6288ctl.h"

SYN6288Ctl::SYN6288Ctl(QObject *parent)
    : QObject{parent}
{
    memset(buffer, 0, sizeof(buffer));
    fd = open(uartDevice.toUtf8().data(), O_RDWR | O_NOCTTY);
    if (fd < 0)
        qDebug()<<"open syn6288 error";
    else
    {
        qDebug()<<"open syn6288 successfully"<<uartDevice;
        set_opt(fd, 9600, 8, 'N', 1);
        SYN_FrameInfo(1, UTF8ToGB2312("语音模块启动成功！"));
    }
}

int SYN6288Ctl::set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio, oldtio;
    if (tcgetattr(fd, &oldtio) != 0)
    {
        qDebug()<<"SetupSerial 1";
        return -1;
    }
    bzero(&newtio, sizeof(newtio));

    newtio.c_cflag |= CLOCAL | CREAD;

    newtio.c_cflag &= ~CSIZE;

    switch (nBits)
    {
    case 5:
        newtio.c_cflag |= CS5;
        break;
    case 6:
        newtio.c_cflag |= CS6;
        break;
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }

    switch (nEvent)
    {
    case 'O':
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E':
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':
        newtio.c_cflag &= ~PARENB;
        newtio.c_iflag &= ~INPCK;
        newtio.c_iflag &= ~ISTRIP;
        break;
    }

    switch (nSpeed)
    {
    case 2400:
        cfsetispeed(&newtio, B2400);
        cfsetospeed(&newtio, B2400);
        break;
    case 4800:
        cfsetispeed(&newtio, B4800);
        cfsetospeed(&newtio, B4800);
        break;
    case 9600:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    case 460800:
        cfsetispeed(&newtio, B460800);
        cfsetospeed(&newtio, B460800);
        break;
    default:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    }
    if (nStop == 1)
        newtio.c_cflag &= ~CSTOPB;
    else if (nStop == 2)
        newtio.c_cflag |= CSTOPB;

    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 0;

    tcflush(fd, TCIOFLUSH);

    if ((tcsetattr(fd, TCSANOW, &newtio)) != 0)
    {
        qDebug()<<"com set error";
        return -1;
    }

    return 0;
}

void SYN6288Ctl::SYN_FrameInfo(uint8_t Music, char *HZdata)
{
    /****************需要发送的文本**********************************/
    unsigned char Frame_Info[50];
    unsigned char HZ_Length;
    unsigned char ecc = 0; // 定义校验字节
    unsigned int i = 0;
    HZ_Length = strlen((char*)HZdata); // 需要发送文本的长度

    /*****************帧固定配置信息**************************************/
    Frame_Info[0] = 0xFD;              // 构造帧头FD
    Frame_Info[1] = 0x00;              // 构造数据区长度的高字节
    Frame_Info[2] = HZ_Length + 3;     // 构造数据区长度的低字节
    Frame_Info[3] = 0x01;              // 构造命令字：合成播放命令
    Frame_Info[4] = 0x01 | Music << 4; // 构造命令参数：背景音乐设定

    /*******************校验码计算***************************************/
    for (i = 0; i < 5; i++) // 依次发送构造好的5个帧头字节
    {
        ecc = ecc ^ (Frame_Info[i]); // 对发送的字节进行异或校验
    }

    for (i = 0; i < HZ_Length; i++) // 依次发送待合成的文本数据
    {
        ecc = ecc ^ (HZdata[i]); // 对发送的字节进行异或校验
    }
    /*******************发送帧信息***************************************/
    memcpy(&Frame_Info[5], HZdata, HZ_Length);
    Frame_Info[5 + HZ_Length] = ecc;
    // PrintCom(Frame_Info, 5 + HZ_Length + 1);
    write(fd, Frame_Info, 5 + HZ_Length + 1);

}

char *SYN6288Ctl::UTF8ToGB2312(char *strUtf8)
{
    QTextCodec* utf8Codec= QTextCodec::codecForName("utf-8");
    QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

    QString strUnicode= utf8Codec ->toUnicode(strUtf8);
    QByteArray ByteGb2312= gb2312Codec ->fromUnicode(strUnicode);

    return ByteGb2312.data();
}


