#include "tcpserver.h"

#include <QThread>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

CTcpServer::CTcpServer(QObject *parent)
    : QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

CTcpServer::~CTcpServer()
{
    qDebug() << "destruct CTcpServer" << endl;
    this->close();
}

void CTcpServer::newConnection()
{
    QTcpSocket *socket = nextPendingConnection();

    if(socket && socket->state() == QAbstractSocket::ConnectedState){
        qDebug() << "new connection is comming from " 
        << socket->peerAddress().toString() << ":" << socket->peerPort() << endl;

        connect(socket, &QTcpSocket::readyRead, this, &CTcpServer::readyRead);
        connect(socket, &QTcpSocket::disconnected, this, &CTcpServer::socketDisconnect);
    }
}

void CTcpServer::readyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*> (sender());
    QByteArray ba = socket->readAll();
    qDebug() << "receive data from " 
    << socket->peerAddress().toString() << ":" << socket->peerPort() << ":" << endl << ba.data();

    if(clientGroupA.find(socket) != clientGroupA.end()){
        forwardMsg(GroupA, ba);
        return;
    }
    else if(clientGroupB.find(socket) != clientGroupB.end()){
        forwardMsg(GroupB, ba);
        return;
    }

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(ba, &err);
    if(doc.isNull()){
        qDebug() << "the received data is not a valid json doc, " << err.errorString() << endl;
        return;
    }

    QJsonObject json = doc.object();
    if(json.contains("name") && json["name"].isString())
    {
        QString name = json["name"].toString();
        if(name == "clientA"){
            clientGroupA.insert(socket);
            forwardMsg(GroupA, ba);
        }
        else if(name == "clientB"){
            clientGroupB.insert(socket);
            forwardMsg(GroupB, ba);
        }
    }
}

void CTcpServer::forwardMsg(const int group, const QByteArray &ba)
{
    if(group == GroupA){
        QSet<QTcpSocket*>::iterator iter = clientGroupB.begin();
        for(; iter != clientGroupB.end(); ++iter){
            QTcpSocket *socket = *iter;
            socket->write(ba);
        }
    }
    else if(group == GroupB){
        QSet<QTcpSocket*>::iterator iter = clientGroupA.begin();
        for(; iter != clientGroupA.end(); ++iter){
            QTcpSocket *socket = *iter;
            socket->write(ba);
        }
    }
}

void CTcpServer::socketDisconnect()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*> (sender());
    qDebug() << "socket " << socket->localAddress().toString() << " disconnected" << endl;
}

