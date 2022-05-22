
#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "./tcpserver/tcpserver.h"

void initForwardTcpServer(QObject *parent);

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    qDebug() << "this is a jserver instance." << endl;

    initForwardTcpServer(&app);

    return app.exec();
}

void initForwardTcpServer(QObject *parent)
{
    CTcpServer *server = new CTcpServer(parent);
    server->listen(QHostAddress::Any, 8888);
}





