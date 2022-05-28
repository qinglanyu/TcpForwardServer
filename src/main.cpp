
#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "./tcpserver/tcpserver.h"

void initForwardTcpServer(QObject *parent, int argc, char* argv[]);

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    if((argc != 1) && (argc != 2)){
        qDebug() << QString("param count(%1) error.").arg(argc) << endl;
        qDebug() << "usage: " << endl;
        qDebug() << "./jserver 2354     # start a server listening port 2345" << endl;
        qDebug() << "./jserver          # start a server listening port 8888" << endl;
        return -1;
    }

    initForwardTcpServer(&app, argc, argv);

    return app.exec();
}

void initForwardTcpServer(QObject *parent, int argc, char* argv[])
{
    qDebug() << "this is a jserver instance." << endl;

    CTcpServer *server = new CTcpServer(parent);

    if(1 == argc){
        server->listen(QHostAddress::Any, 8888);
    }
    else{
        server->listen(QHostAddress::Any, atoi(argv[1]));
    }
}





