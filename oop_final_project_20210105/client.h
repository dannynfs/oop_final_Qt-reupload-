#pragma once

#include <QWidget>
#include <qtcpsocket.h>

struct recv_Struct {
    int x1;
    int y1;
    int acting_1;
    int direction_1;
    int jumped_1;
    int winner_1;

    int x2;
    int y2;
    int acting_2;
    int direction_2;
    int jumped_2;
    int winner_2;

    int x3;
    int y3;
    int acting_3;
    int direction_3;
    int jumped_3;
    int winner_3;

    int x4;
    int y4;
    int acting_4;
    int direction_4;
    int jumped_4;
    int winner_4;
};

struct SendStruct {
    int identity=0;
    int x=0;
    int y=0;
    int acting=0;
    int direction=0;
    int jumped=0;
    int winner=0;
};
struct trapStruct {

    int item1 = 0;
    int x1 = 0;
    int y1 = 0;
    int item2 = 0;
    int x2 = 0;
    int y2 = 0;
    int OK_status=100;
    
};

class client : public QWidget
{
    Q_OBJECT

public:
    client( QWidget* parent = Q_NULLPTR);

    QTcpSocket* m_socket;

    void connectToServer();

    recv_Struct gamemode_ReadMessage(); //gamemode_read
    QString select_ReadMessage(); //select_read
    trapStruct trap_ReadMessage();//trap_read
    
    void sendMessage(SendStruct);//gamemode_send
    void sendMessage(trapStruct);//trap_send
    void sendMessage(QString);//select_send

    int port;
};