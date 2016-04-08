#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QFile>
#include <QTest>

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = 0);

    void connectSocket();
    void send(QByteArray trame);
    void setIP(QString s);

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    QByteArray getBuffer();

private:
    bool connecter;
    QTcpSocket *socket;
    QString IP;
    QByteArray buffer;

};


#endif // SOCKET_H
