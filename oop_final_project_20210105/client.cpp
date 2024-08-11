#include "client.h"
#include <QHostAddress>

client::client(QWidget* parent)
    : QWidget(parent)
{
}
void client::connectToServer()
{
    m_socket = new QTcpSocket(this);

    //連線到伺服器

    m_socket->connectToHost("10.101.2.8",port);

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(ReadMessage()));
}

QString client::select_ReadMessage()   //select_read
{
    return m_socket->readAll().data();
}

void client::sendMessage(QString str)  //select_send
{
    m_socket->write(str.toUtf8());
}

recv_Struct client::gamemode_ReadMessage()   // gamemode_read
{
    struct recv_Struct pos;
    m_socket->read((char*)&pos, sizeof(pos));
    return pos;
}

void client::sendMessage(SendStruct pos) // gamemode_send
{
    m_socket->write((char*)&pos, sizeof(pos));
}

trapStruct client::trap_ReadMessage()   // trap_read
{
    //struct trapFinal trap_each_recieve;
    struct trapStruct trap_each;
    m_socket->read((char*)&trap_each, sizeof(trap_each));
    return trap_each;
}

void client::sendMessage(trapStruct trap_each) //trap_send
{
    m_socket->write((char*)&trap_each, sizeof(trap_each));
}