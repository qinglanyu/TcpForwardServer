#ifndef __INC_TCP_SERVER
#define __INC_TCP_SERVER

#include <QTcpServer>
#include <QSet>

class QNetworkSession;

class CTcpServer : public QTcpServer   
{
    Q_OBJECT
public:
    enum clientGroup{
        GroupA,
        GroupB
    };
    Q_ENUM(clientGroup)

    explicit CTcpServer(QObject *parent = nullptr);
    virtual ~CTcpServer();

protected:
    void forwardMsg(const int group, const QByteArray& ba);

private slots:
    void newConnection();
    void readyRead();
    void socketDisconnect(); 

private:
    QSet<QTcpSocket*> clientGroupA, clientGroupB;
};




#endif


