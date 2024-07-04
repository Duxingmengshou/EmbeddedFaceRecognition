#ifndef UDPCOM_H
#define UDPCOM_H

#include <QUdpSocket>
#include <QIODevice>
#include <QObject>
#include <QDebug>
#include <vector>
#include <algorithm>
#include <QCryptographicHash>
#include <QtMath>
#include <QThread>
#include <QMutex>
class UDPCom : public QThread
{
    Q_OBJECT
public:
    explicit UDPCom(QObject *parent = nullptr);
    void run();
public:
    QMutex bufMutex;
signals:
    void newMessage(QByteArray data);
public slots:
    void recive();
    void sendData(QByteArray msg,QHostAddress address,quint16 port);
private:
    QUdpSocket *socket;
};

#endif // UDPCOM_H
