#include "mavlinkcontroller.h"

MavlinkController::MavlinkController(QObject *parent)
    : QObject{parent}
{}

TCPConnectionController *MavlinkController::connectionController() const
{
    return m_connectionController;
}

void MavlinkController::setConnectionController(TCPConnectionController *newConnectionController)
{
    if (m_connectionController == newConnectionController)
        return;
    if (m_connectionController)
    {
        // disconnect
        disconnect(m_connectionController, &TCPConnectionController::onReadBytes, this, &MavlinkController::processBytes);
    }
    m_connectionController = newConnectionController;
    emit connectionControllerChanged();

    connect(m_connectionController, &TCPConnectionController::onReadBytes, this, &MavlinkController::processBytes);
}

void MavlinkController::processBytes(const QByteArray &data)
{

}
