#include "tcpconnectioncontroller.h"

TCPConnectionController::TCPConnectionController(QObject *parent)
    : QObject{parent}
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::stateChanged, this, &TCPConnectionController::sockState);
    connect(m_socket, &QTcpSocket::readyRead, this, &TCPConnectionController::readBytes);
    // reset class
    disconnectFrom();
}

void TCPConnectionController::connectTo(const QString &host, int port)
{
    disconnectFrom();
    setState(tr("Подключение к %1:%2").arg(host).arg(port));
    // setIsConnected(true);
    m_socket->connectToHost(QHostAddress(host), port);
}

void TCPConnectionController::disconnectFrom()
{
    if (m_socket->state() != QTcpSocket::UnconnectedState)
        m_socket->disconnectFromHost();
    setState(tr("Ожидаю подключения"));
    setIsConnected(false);
}

QString TCPConnectionController::state() const
{
    return m_state;
}

void TCPConnectionController::setState(const QString &newState)
{
    if (m_state == newState)
        return;
    m_state = newState;
    emit stateChanged();
}

bool TCPConnectionController::isConnected() const
{
    return m_isConnected;
}

void TCPConnectionController::setIsConnected(bool newIsConnected)
{
    if (m_isConnected == newIsConnected)
        return;
    m_isConnected = newIsConnected;
    emit isConnectedChanged();
}

void TCPConnectionController::sockState(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::UnconnectedState:
        setIsConnected(false);
        setState(tr("Разъединен"));
        break;
    case QAbstractSocket::HostLookupState:
        setIsConnected(false);
        setState(tr("Поиск хоста"));
        break;
    case QAbstractSocket::ConnectingState:
        setIsConnected(false);
        setState(tr("Соединение"));
        break;
    case QAbstractSocket::ConnectedState:
        setIsConnected(true);
        setState(tr("Соединен"));
        break;
    case QAbstractSocket::BoundState:
        setIsConnected(false);
        setState(tr("Bound"));
        break;
    case QAbstractSocket::ListeningState:
        setIsConnected(false);
        setState(tr("Чтение..."));
        break;
    case QAbstractSocket::ClosingState:
        setIsConnected(false);
        setState(tr("Разъединение..."));
        break;
    default:
        break;
    }
}

void TCPConnectionController::readBytes()
{
    auto buff = m_socket->readAll();
    // read
    emit onReadBytes(buff);
    setOnReaded(buff.size());
}

int TCPConnectionController::onReaded() const
{
    return m_onReaded;
}

void TCPConnectionController::setOnReaded(int newOnReaded)
{
    if (m_onReaded == newOnReaded)
        return;
    m_onReaded = newOnReaded;
    emit onReadedChanged();
}

void TCPConnectionController::writeBytes(const QByteArray &data)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState)
    {
        m_socket->write(data);
    }
}
