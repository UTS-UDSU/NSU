#ifndef TCPCONNECTIONCONTROLLER_H
#define TCPCONNECTIONCONTROLLER_H

#include <QObject>
#include <QTcpSocket>

class TCPConnectionController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged FINAL)
    Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged FINAL)
    Q_PROPERTY(int onReaded READ onReaded WRITE setOnReaded NOTIFY onReadedChanged FINAL)
public:
    explicit TCPConnectionController(QObject *parent = nullptr);

    Q_INVOKABLE void connectTo(const QString &host, int port);
    Q_INVOKABLE void disconnectFrom();

    QString state() const;
    void setState(const QString &newState);

    bool isConnected() const;
    void setIsConnected(bool newIsConnected);
    int onReaded() const;
    void setOnReaded(int newOnReaded);

    void writeBytes(const QByteArray &data);

private slots:

    void sockState(QAbstractSocket::SocketState state);
    void readBytes();
signals:
    void stateChanged();
    void isConnectedChanged();
    void onReadedChanged();

    void onReadBytes(const QByteArray &data);

private:
    QString m_state;
    bool m_isConnected;

    QTcpSocket *m_socket = nullptr;
    int m_onReaded;
};

#endif // TCPCONNECTIONCONTROLLER_H
