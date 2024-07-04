#include "udpcom.h"

UDPCom::UDPCom(QObject *parent)
    : QThread{parent}
{
    socket = new QUdpSocket();
    if(!socket->bind(QHostAddress::Any,4321))
        qDebug()<<"bind error!";
    connect(socket,&QUdpSocket::readyRead,this,&UDPCom::recive);
}

void UDPCom::run()
{
//    while(1){
//        if(isSend)
//        {
//            bufMutex.lock();
//            isSend=false;
//            sendDataDefault(buf);
//            buf.clear();
//            bufMutex.unlock();
//            qDebug()<<"send img ok";
//        }
//    }
}

void UDPCom::sendData(QByteArray msg, QHostAddress address, quint16 port)
{
    //    socket->writeDatagram(msg,address,port);
    int size = msg.size();
    int count = qCeil(static_cast<qreal>(size) / 65472);
    int array_pos_start = 0;
    while (count) {
        int array_pos_end = qMin(size, array_pos_start + 65472);
        QByteArray packet;
        packet.append(static_cast<char>(count));
        packet.append(msg.mid(array_pos_start, array_pos_end - array_pos_start));
        socket->writeDatagram(packet, address, port);
        array_pos_start = array_pos_end;
        count -= 1;
    }
}


void UDPCom::recive()
{
    while(socket->hasPendingDatagrams())
    {
        QByteArray ba;
        ba.resize(socket->pendingDatagramSize());
        QHostAddress peerAddress;
        quint16 peerPort;
        socket->readDatagram(ba.data(),ba.size(),&peerAddress,&peerPort);
        emit newMessage(ba);
        qDebug()<<"message";
        qDebug()<<ba;
    }
}

