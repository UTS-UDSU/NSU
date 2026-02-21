#ifndef MAVLINKCONTROLLER_H
#define MAVLINKCONTROLLER_H

#include <QObject>
#include "tcpconnectioncontroller.h"

class MavlinkController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TCPConnectionController* connectionController READ connectionController WRITE setConnectionController NOTIFY connectionControllerChanged FINAL)
public:
    explicit MavlinkController(QObject *parent = nullptr);

    TCPConnectionController *connectionController() const;
    void setConnectionController(TCPConnectionController *newConnectionController);

private:

    TCPConnectionController *m_connectionController = nullptr;

private slots:

    void processBytes(const QByteArray &data);

signals:
    void connectionControllerChanged();
};

#endif // MAVLINKCONTROLLER_H
