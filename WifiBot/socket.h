#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = 0);

    void connectSocket();
    void send(QByteArray trame);

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    bool connecter;
    QTcpSocket *socket;

};


#endif // SOCKET_H
