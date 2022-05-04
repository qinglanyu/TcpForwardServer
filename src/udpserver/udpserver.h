#ifndef __INC_UDP_SERVER
#define __INC_UDP_SERVER


#include <QObject>

class QUdpSocket;
class QNetworkDatagram;

class CUdpServer : public QObject
{
    Q_OBJECT
public:
    CUdpServer();
    ~CUdpServer();
    void initSocket();

public slots:
    void readPendingDatagrams();

protected:
    void processTheDatagram(const QNetworkDatagram& );

private:
    QUdpSocket *udpSocket;
};


#endif


