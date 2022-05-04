#include "udpserver.h"
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QByteArray>
#include <QDebug>

const quint16 SVR_LISTEN_PORT = 6666;

CUdpServer::CUdpServer()
    : udpSocket(nullptr)
{

}


CUdpServer::~CUdpServer()
{
    if(udpSocket){
        delete udpSocket;
        udpSocket = nullptr;
    }
}

void CUdpServer::initSocket()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, SVR_LISTEN_PORT);

    connect(udpSocket, &QUdpSocket::readyRead, this, &CUdpServer::readPendingDatagrams);
}

void CUdpServer::readPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams()){
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        processTheDatagram(datagram);
    }
}

void CUdpServer::processTheDatagram(const QNetworkDatagram& d)
{
    const QByteArray ba = d.data();
    qDebug() << "receive data from " << d.senderAddress().toString() << " :" << QString(ba.data()) << endl;
}




