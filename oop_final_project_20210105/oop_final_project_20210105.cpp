#include "oop_final_project_20210105.h"
#include "Role.h"
#include"trap.h"
#include<QPixmap>
#include <QPainter>
#include<QPaintEvent>
#include <QKeyEvent>
#include <QMouseEvent>
int map[10][19] = {
        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0 },
        { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
        { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
        { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
        { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
};

int role_choose = 0;
int winFinal = 0;
bool flag = false;

oop_final_project_20210105::oop_final_project_20210105(QWidget* parent)
    : QMainWindow(parent)
{
    // ui.setupUi(this);
    setFixedSize(1900, 1000);
    stack = new QStackedWidget();
    stack->addWidget(new startWidget(stack));
    setCentralWidget(stack);

}



playmode::playmode(QStackedWidget* stackedWidget, QWidget* parent) {

    player.port = 4896;
    player.connectToServer();
    time = startTimer(100);
    R1 = new Role(5, 0);
    R1->setPixelPosition_x(0);
    R1->setPixelPosition_y(500);
    package.x1 = 5;
    package.x2 = 5;
    package.x3 = 5;
    package.x4 = 5;
    package.y1 = 0;
    package.y2 = 0;
    package.y3 = 0;
    package.y4 = 0;
    package.acting_1 = 0;
    package.acting_2 = 0;
    package.acting_3 = 0;
    package.acting_4 = 0;
    package.direction_1 = 0;
    package.direction_2 = 0;
    package.direction_3 = 0;
    package.direction_4 = 0;
    package.jumped_1 = 0;
    package.jumped_2 = 0;
    package.jumped_3 = 0;
    package.jumped_4 = 0;
    package.winner_1 = 0;
    package.winner_2 = 0;
    package.winner_3 = 0;
    package.winner_4 = 0;


    int cnt = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 19; j++) {
            if (map[i][j] == 5) {
                Arch[cnt] = new arch(i, j);
                Arch[cnt]->setPixelPosition_x(Arch[cnt]->getInitial_y() * 100);
                Arch[cnt]->setPixelPosition_y(Arch[cnt]->getInitial_x() * 100-10);
                Arch[cnt]->setPosition_x(Arch[i]->getInitial_x()-1);
                Arch[cnt]->setPosition_y(Arch[i]->getInitial_y());
                Arch[cnt]->setLife(true);
                cnt++;
            }
        }
    }
    arch_num = cnt;


    other_1 = new Role(0, 0);
    other_2 = new Role(0, 0);
    other_3 = new Role(0, 0);
    other_4 = new Role(0, 0);

    other_1->setIdentify(1);
    other_2->setIdentify(2);
    other_3->setIdentify(3);
    other_4->setIdentify(4);


    R1->R_run = 0;
    R1->L_run = 0;
    R1->R_jump = 0;
    R1->L_jump = 0;
    R1->acting = 0;
    baseWidget_p = stackedWidget;
}

void playmode::paintEvent(QPaintEvent* event)
{


    // painter declare
    QPixmap pixmapBackground = QPixmap("../OOP_Photo/background/sky.jpg").scaled(this->size());
    QPainter painter(this);
    painter.drawPixmap(this->rect(), pixmapBackground);

    QPainter painter1(this);
    painter1.setRenderHint(QPainter::Antialiasing, true);


    //tcp

    R1->setIdentify(role_choose);

    //Local player 
    //info to server
    Sendpos.identity = R1->getIdentify();//選擇腳色介面要給值判定
    Sendpos.x = R1->getPixelPosition_x();
    Sendpos.y = R1->getPixelPosition_y();
    Sendpos.acting = R1->acting;
    Sendpos.direction = R1->getDirection();
    Sendpos.jumped = R1->getJumped();
    if (R1->getPixelPosition_x() >= 1800) {
        Sendpos.winner = R1->getIdentify();
    }

    // send message to server
    player.sendMessage(Sendpos);

    // recieve message  from server


    package = player.gamemode_ReadMessage();


    if ((package.winner_1 > 0&& package.winner_1<=4) ||
        (package.winner_2 > 0 && package.winner_2 <= 4)||
        (package.winner_3 > 0 && package.winner_3 <= 4) > 0 ||
        (package.winner_4 > 0 && package.winner_4 <= 4) > 0)
    {
        winFinal = package.winner_1;
        creatEndWidget();
    }

    bool useLess[4] = { 0 };

    other_1->setPixelPosition_x(package.x1);
    other_1->setPixelPosition_y(package.y1);
    other_1->acting = package.acting_1;
    other_1->setDirection(package.direction_1);
    other_1->setJumped(package.jumped_1);
    if (R1->getIdentify() == 1)useLess[0] = 1;

    other_2->setPixelPosition_x(package.x2);
    other_2->setPixelPosition_y(package.y2);
    other_2->acting = package.acting_2;
    other_2->setDirection(package.direction_2);
    other_2->setJumped(package.jumped_2);
    if (R1->getIdentify() == 2)useLess[1] = 1;

    other_3->setPixelPosition_x(package.x3);
    other_3->setPixelPosition_y(package.y3);
    other_3->acting = package.acting_3;
    other_3->setDirection(package.direction_3);
    other_3->setJumped(package.jumped_3);
    if (R1->getIdentify() == 3)useLess[2] = 1;

    other_4->setPixelPosition_x(package.x4);
    other_4->setPixelPosition_y(package.y4);
    other_4->acting = package.acting_4;
    other_4->setDirection(package.direction_4);
    other_4->setJumped(package.jumped_4);
    if (R1->getIdentify() == 4)useLess[3] = 1;


    //設定重力.位置
    R1->setPosition_x((R1->getPixelPosition_y() + 48) / 100);
    R1->setPosition_y((R1->getPixelPosition_x() + 50) / 100);
    R1->setSpeed_y(R1->getSpeed_y() + 10);//gravity

    ////////////////////////////////////////////////////////////////////////
    //                                                 偵測點                                                         //
    ////////////////////////////////////////////////////////////////////////

    //右上偵測點
    //右下偵測點
    int right_j = (R1->getPixelPosition_x() + 65 + R1->getSpeed_x()) / 100;
    int upper_right_i = (R1->getPixelPosition_y() + 25) / 100;
    int lower_right_i = (R1->getPixelPosition_y() + 75) / 100;

    //左上偵測點
    //左下偵測點
    int left_j = (R1->getPixelPosition_x() + R1->getSpeed_x()) / 100;
    int upper_left_i = (R1->getPixelPosition_y() + 25) / 100;
    int lower_left_i = (R1->getPixelPosition_y() + 75) / 100;

    //左下角偵測點
   //右下角偵測點
    int lower_i = (R1->getPixelPosition_y() + 98 + R1->getSpeed_y()) / 100;
    int lower_left_j = (R1->getPixelPosition_x() + 30) / 100;
    int lower_right_j = (R1->getPixelPosition_x() + 70) / 100;

    //左上角偵測點
    //右下角偵測點
    int upper_i = (R1->getPixelPosition_y() + R1->getSpeed_y()) / 100;
    int upper_left_j = (R1->getPixelPosition_x() + 30) / 100;
    int upper_right_j = (R1->getPixelPosition_x() + 70) / 100;



    //trap
    // spike ice net 只需判定腳下
    if (map[R1->getPosition_x() + 1][R1->getPosition_y()] == 2) {//spike dead
        R1->setLife(false);
    }
    else if (map[R1->getPosition_x() + 1][R1->getPosition_y()] == 3) {  //ice 
        if (R1->getDirection() == 1)R1->setSpeed_x(30);
        else if (R1->getDirection() == 2)R1->setSpeed_x(-30);
    }
    else if (map[R1->getPosition_x() + 1][R1->getPosition_y()] == 4 && (R1->getSpeed_x() > 10 || R1->getSpeed_x() < -10)) {  //net
        if (R1->getDirection() == 1)R1->setSpeed_x(10);
        else if (R1->getDirection() == 2)R1->setSpeed_x(-10);
    }

    //teleport偵測

    //右上偵測點
    //右下偵測點
    int right_j_for_teleport = (R1->getPixelPosition_x() + 55) / 100;
    int upper_right_i_for_teleport = (R1->getPixelPosition_y() + 25) / 100;
    int lower_right_i_for_teleport = (R1->getPixelPosition_y() + 75) / 100;

    //左上偵測點
    //左下偵測點
    int left_j_for_teleport = (R1->getPixelPosition_x() + 45) / 100;
    int upper_left_i_for_teleport = (R1->getPixelPosition_y() + 25) / 100;
    int lower_left_i_for_teleport = (R1->getPixelPosition_y() + 75) / 100;

    //左下角偵測點
    //右下角偵測點
    int lower_i_for_teleport = (R1->getPixelPosition_y() + 75) / 100;
    int lower_left_j_for_teleport = (R1->getPixelPosition_x() + 45) / 100;
    int lower_right_j_for_teleport = (R1->getPixelPosition_x() + 55) / 100;

    //左上角偵測點
    //右下角偵測點
    int upper_i_for_teleport = (R1->getPixelPosition_y() + 25) / 100;
    int upper_left_j_for_teleport = (R1->getPixelPosition_x() + 45) / 100;
    int upper_right_j_for_teleport = (R1->getPixelPosition_x() + 55) / 100;

    // teleport arch 四個方向都要進行偵測
    if ((map[upper_right_i_for_teleport][right_j_for_teleport] == 6) || (map[lower_right_i_for_teleport][right_j_for_teleport] == 6)
        || (map[upper_left_i_for_teleport][left_j_for_teleport] == 6) || (map[lower_left_i_for_teleport][left_j_for_teleport] == 6)
        || (map[lower_i_for_teleport][lower_left_j_for_teleport] == 6) || (map[lower_i_for_teleport][lower_right_j_for_teleport] == 6)
        || (map[upper_i_for_teleport][upper_left_j_for_teleport] == 6) || (map[upper_i_for_teleport][upper_right_j_for_teleport] == 6)) {
        R1->setLife(false);
    }


    //箭的初始位置

    for (int i = 0; i < arch_num; i++) {


        if (Arch[i]->getPixelPosition_y() <= 0) {
            map[Arch[i]->getPosition_x()][Arch[i]->getPosition_y()] = 0;

            Arch[i]->setLife(false);
        }
        if (Arch[i]->getLife() == false) {
            int x = Arch[i]->getPosition_x();
            int y = Arch[i]->getPosition_y();
            Arch[i]->setPixelPosition_x(Arch[i]->getInitial_y() * 100);
            Arch[i]->setPixelPosition_y(Arch[i]->getInitial_x() * 100 - 1);
            Arch[i]->setPosition_x(Arch[i]->getInitial_x() - 1);
            Arch[i]->setPosition_y(Arch[i]->getInitial_y());
            map[Arch[i]->getPosition_x()][Arch[i]->getPosition_y()] = 7;
            Arch[i]->setLife(true);
        }
        else {

            int x = Arch[i]->getPosition_x();
            int y = Arch[i]->getPosition_y();
            Arch[i]->setPosition_x(Arch[i]->getPixelPosition_y() / 100);
            Arch[i]->setPosition_y((Arch[i]->getPixelPosition_x()) / 100);

            if (x >= 0 && x <= 9) {
                int temp = map[Arch[i]->getPosition_x()][Arch[i]->getPosition_y()];
                map[Arch[i]->getPosition_x()][Arch[i]->getPosition_y()] = map[x][y];
                map[x][y] = temp;
            }
            Arch[i]->setPixelPosition_y(Arch[i]->getPixelPosition_y() - 25);

        }

    }


    

    //右上偵測點
    //右下偵測點
    int right_j_for_rocket = (R1->getPixelPosition_x() + 55) / 100;
    int upper_right_i_for_rocket = (R1->getPixelPosition_y() + 25) / 100;
    int lower_right_i_for_rocket = (R1->getPixelPosition_y() + 75) / 100;

    //左上偵測點
    //左下偵測點
    int left_j_for_rocket = (R1->getPixelPosition_x() + 45) / 100;
    int upper_left_i_for_rocket = (R1->getPixelPosition_y() + 25) / 100;
    int lower_left_i_for_rocket = (R1->getPixelPosition_y() + 75) / 100;

    //左下角偵測點
    //右下角偵測點
    int lower_i_for_rocket = (R1->getPixelPosition_y() + 75) / 100;
    int lower_left_j_for_rocket = (R1->getPixelPosition_x() + 45) / 100;
    int lower_right_j_for_rocket = (R1->getPixelPosition_x() + 55) / 100;

    //左上角偵測點
    //右下角偵測點
    int upper_i_for_rocket = (R1->getPixelPosition_y() + 25) / 100;
    int upper_left_j_for_rocket = (R1->getPixelPosition_x() + 45) / 100;
    int upper_right_j_for_rocket = (R1->getPixelPosition_x() + 55) / 100;

    // teleport arch 四個方向都要進行偵測
    if ((map[upper_right_i_for_rocket][right_j_for_rocket] == 7) || (map[lower_right_i_for_rocket][right_j_for_rocket] == 7)
        || (map[upper_left_i_for_rocket][left_j_for_rocket] == 7) || (map[lower_left_i_for_rocket][left_j_for_rocket] == 7)
        || (map[lower_i_for_rocket][lower_left_j_for_rocket] == 7) || (map[lower_i_for_rocket][lower_right_j_for_rocket] == 7)
        || (map[upper_i_for_rocket][upper_left_j_for_rocket] == 7) || (map[upper_i_for_rocket][upper_right_j_for_rocket] == 7)) {
        R1->setLife(false);
    }


    // transport to spawn
    if (R1->getPosition_x() >= 9 || R1->getPosition_x() < 0 || R1->getPosition_y() < 0) {
        R1->setLife(false);

    }
    if (R1->getLife() == false) {
        R1->setSpeed_y(0);
        R1->setPosition_x(5);
        R1->setPosition_y(0);
        R1->setPixelPosition_x(0);
        R1->setPixelPosition_y(500);
        R1->setLife(true);
    }

    //moving

    if (R1->getSpeed_x() > 0) {
        R1->setSpeed_x(R1->getSpeed_x() - R1->getFriction());//friction
    }
    else if (R1->getSpeed_x() < 0) {
        R1->setSpeed_x(R1->getSpeed_x() + R1->getFriction());
    }

    //偵測左右碰撞
    if ((map[upper_right_i][right_j] >= 1 && map[upper_right_i][right_j] <= 5) || (map[lower_right_i][right_j] >= 1 && map[lower_right_i][right_j] <= 5) || (map[upper_left_i][left_j] >= 1 && map[upper_left_i][left_j] <= 5) || (map[lower_left_i][left_j] >= 1 && map[lower_left_i][left_j] <= 5)) {
        R1->setSpeed_x(0);
    }
    else R1->setPixelPosition_x(R1->getPixelPosition_x() + R1->getSpeed_x());//x moving 


    //偵測上下碰撞
    if ((map[lower_i][lower_left_j] >= 1 && map[lower_i][lower_left_j] <= 5) || (map[lower_i][lower_right_j] >= 1 && map[lower_i][lower_right_j] <= 5)) {
        R1->setPixelPosition_y((lower_i - 1) * 100);
        R1->setSpeed_y(0);
    }
    else if ((map[upper_i][upper_left_j] >= 1 && map[upper_i][upper_left_j] <= 5) || (map[upper_i][upper_right_j] >= 1 && map[upper_i][upper_right_j] <= 5)) {
        R1->setSpeed_y(0);
    }
    else R1->setPixelPosition_y(R1->getPixelPosition_y() + R1->getSpeed_y());//y moving

    //set move state
    if (R1->getSpeed_x() == 0 && R1->getSpeed_y() == 0) R1->acting = 0;
    if (R1->getSpeed_x() != 0 || R1->getSpeed_y() != 0) R1->acting = 1;



    // Role1 action
    if (R1->acting == 1 && R1->getJumped() == 1) {
        R1->R_jump++;
        R1->L_jump++;
        R1->R_run = 0;
        R1->L_run = 0;
    }
    else if (R1->acting == 1) {
        R1->R_run++;
        R1->L_run++;
        R1->R_jump = 0;
        R1->L_jump = 0;
    }
    //other role action
    if (useLess[0] == 0) {
        if (other_1->acting == 1 && other_1->getJumped() == 1) {
            other_1->R_jump++;
            other_1->L_jump++;
            other_1->R_run = 0;
            other_1->L_run = 0;
        }
        else if (other_1->acting == 1) {
            other_1->R_run++;
            other_1->L_run++;
            other_1->R_jump = 0;
            other_1->L_jump = 0;
        }
    }
    if (useLess[1] == 0) {
        if (other_2->acting == 1 && other_2->getJumped() == 1) {
            other_2->R_jump++;
            other_2->L_jump++;
            other_2->R_run = 0;
            other_2->L_run = 0;
        }
        else if (other_2->acting == 1) {
            other_2->R_run++;
            other_2->L_run++;
            other_2->R_jump = 0;
            other_2->L_jump = 0;
        }
    }
    if (useLess[2] == 0) {
        if (other_3->acting == 1 && other_3->getJumped() == 1) {
            other_3->R_jump++;
            other_3->L_jump++;
            other_3->R_run = 0;
            other_3->L_run = 0;
        }
        else if (other_3->acting == 1) {
            other_3->R_run++;
            other_3->L_run++;
            other_3->R_jump = 0;
            other_3->L_jump = 0;
        }
    }
    if (useLess[3] == 0) {
        if (other_4->acting == 1 && other_4->getJumped() == 1) {
            other_4->R_jump++;
            other_4->L_jump++;
            other_4->R_run = 0;
            other_4->L_run = 0;
        }
        else if (other_4->acting == 1) {
            other_4->R_run++;
            other_4->L_run++;
            other_4->R_jump = 0;
            other_4->L_jump = 0;
        }
    }

    for (int i = 0; i < arch_num; i++) {
        painter1.drawPixmap(Arch[i]->getPixelPosition_x(), Arch[i]->getPixelPosition_y(), QPixmap("../OOP_Photo/item/rocket.png"));
    }

    //print map
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 19; j++) {
            if (map[i][j] == 1) {//brick
                painter1.drawPixmap(j * 100, i * 100, QPixmap("../OOP_Photo/brick.png"));
            }
            else if (map[i][j] == 2) {//spikes
                painter1.drawPixmap(j * 100, i * 100 - 36, QPixmap("../OOP_Photo/item/spike.png"));
            }
            else if (map[i][j] == 3) {
                painter1.drawPixmap(j * 100, i * 100, QPixmap("../OOP_Photo/item/ice.png"));
            }
            else if (map[i][j] == 4) {
                painter1.drawPixmap(j * 100, i * 100, QPixmap("../OOP_Photo/item/net.png"));
            }
            else if (map[i][j] == 5) {
                
                painter1.drawPixmap(j*100, i*100, QPixmap("../OOP_Photo/item/rocketstand.png"));  
            }
            else if (map[i][j] == 6) {
                painter1.drawPixmap(j * 100, i * 100, QPixmap("../OOP_Photo/item/teleport.png"));
            }

        }

    }





    //print other role
    if (useLess[0] == 0) {
        if (other_1->acting == 0) {
            if (other_1->getDirection() == 1) {
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_stand.png"));
            }
            else {
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_stand.png"));
            }
        }

        if (other_1->getDirection() == 1 && other_1->getJumped() == 0 && other_1->acting == 1) {
            int judge = other_1->R_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_8.png"));
                break;

            }
        }
        if (R1->getDirection() == 2 && R1->getJumped() == 0 && R1->acting == 1) {
            int judge = other_1->L_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_8.png"));
                break;
            }
        }
        if (other_1->getDirection() == 1 && other_1->getJumped() == 1 && other_1->acting == 1) {
            int judge = other_1->R_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_jump_6.png"));
                break;
            }
        }
        if (other_1->getDirection() == 2 && other_1->getJumped() == 1 && R1->acting == 1) {
            int judge = other_1->L_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_1->getPixelPosition_x(), other_1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_jump_6.png"));
                break;
            }
        }
    }
    if (useLess[1] == 0)
    {
        if (other_2->acting == 0) {
            if (R1->getDirection() == 1) {
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_stand.png"));
            }
            else {
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_stand.png"));
            }
        }

        if (other_2->getDirection() == 1 && other_2->getJumped() == 0 && other_2->acting == 1) {
            int judge = other_2->R_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_8.png"));
                break;

            }
        }
        if (other_2->getDirection() == 2 && other_2->getJumped() == 0 && other_2->acting == 1) {
            int judge = other_2->L_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_8.png"));
                break;
            }
        }
        if (other_2->getDirection() == 1 && other_2->getJumped() == 1 && other_2->acting == 1) {
            int judge = other_2->R_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_jump_6.png"));
                break;
            }
        }
        if (other_2->getDirection() == 2 && other_2->getJumped() == 1 && other_2->acting == 1) {
            int judge = other_2->L_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_2->getPixelPosition_x(), other_2->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_jump_6.png"));
                break;
            }
        }
    }
    if (useLess[2] == 0) {
        if (other_3->acting == 0) {
            if (other_3->getDirection() == 1) {
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_stand.png"));
            }
            else {
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_stand.png"));
            }
        }

        if (other_3->getDirection() == 1 && other_3->getJumped() == 0 && other_3->acting == 1) {
            int judge = other_3->R_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_8.png"));
                break;

            }
        }
        if (other_3->getDirection() == 2 && other_3->getJumped() == 0 && other_3->acting == 1) {
            int judge = other_3->L_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_8.png"));
                break;
            }
        }
        if (other_3->getDirection() == 1 && other_3->getJumped() == 1 && other_3->acting == 1) {
            int judge = other_3->R_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_jump_6.png"));
                break;
            }
        }
        if (other_3->getDirection() == 2 && other_3->getJumped() == 1 && other_3->acting == 1) {
            int judge = other_3->L_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_3->getPixelPosition_x(), other_3->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_jump_6.png"));
                break;
            }
        }
    }
    if (useLess[3] == 0) {
        if (other_4->acting == 0) {
            if (other_4->getDirection() == 1) {
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_stand.png"));
            }
            else {
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_stand.png"));
            }
        }

        if (other_4->getDirection() == 1 && other_4->getJumped() == 0 && other_4->acting == 1) {
            int judge = other_4->R_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_8.png"));
                break;

            }
        }
        if (other_4->getDirection() == 2 && other_4->getJumped() == 0 && other_4->acting == 1) {
            int judge = other_4->L_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_8.png"));
                break;
            }
        }
        if (other_4->getDirection() == 1 && other_4->getJumped() == 1 && other_4->acting == 1) {
            int judge = other_4->R_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_jump_6.png"));
                break;
            }
        }
        if (other_4->getDirection() == 2 && other_4->getJumped() == 1 && other_4->acting == 1) {
            int judge = other_4->L_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(other_4->getPixelPosition_x(), other_4->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_jump_6.png"));
                break;
            }
        }
    }
    ///////////////////////////////////////////////////////////
    //                               character 1                                            //
    //////////////////////////////////////////////////////////
    if (R1->getIdentify() == 1) {

        if (R1->acting == 0) {
            if (R1->getDirection() == 1) {
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_stand.png"));
            }
            else {
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_stand.png"));
            }
        }

        if (R1->getDirection() == 1 && R1->getJumped() == 0 && R1->acting == 1) {
            int judge = R1->R_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_run_8.png"));
                break;

            }
        }
        if (R1->getDirection() == 2 && R1->getJumped() == 0 && R1->acting == 1) {
            int judge = R1->L_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_run_8.png"));
                break;
            }
        }
        if (R1->getDirection() == 1 && R1->getJumped() == 1 && R1->acting == 1) {
            int judge = R1->R_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/R_jump_6.png"));
                break;
            }
        }
        if (R1->getDirection() == 2 && R1->getJumped() == 1 && R1->acting == 1) {
            int judge = R1->L_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character1/L_jump_6.png"));
                break;
            }
        }
    }
    ///////////////////////////////////////////////////////////
    //                               character 2                                            //
    //////////////////////////////////////////////////////////
    else if (R1->getIdentify() == 2) {
        if (R1->acting == 0) {
            if (R1->getDirection() == 1) {
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_stand.png"));
            }
            else {
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_stand.png"));
            }
        }

        if (R1->getDirection() == 1 && R1->getJumped() == 0 && R1->acting == 1) {
            int judge = R1->R_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_run_8.png"));
                break;

            }
        }
        if (R1->getDirection() == 2 && R1->getJumped() == 0 && R1->acting == 1) {
            int judge = R1->L_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_run_8.png"));
                break;
            }
        }
        if (R1->getDirection() == 1 && R1->getJumped() == 1 && R1->acting == 1) {
            int judge = R1->R_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/R_jump_6.png"));
                break;
            }
        }
        if (R1->getDirection() == 2 && R1->getJumped() == 1 && R1->acting == 1) {
            int judge = R1->L_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character2/L_jump_6.png"));
                break;
            }
        }

    }
    ///////////////////////////////////////////////////////////
    //                               character 3                                            //
    //////////////////////////////////////////////////////////
    else if (R1->getIdentify() == 3) {
        if (R1->acting == 0) {
            if (R1->getDirection() == 1) {
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_stand.png"));
            }
            else {
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_stand.png"));
            }
        }

        if (R1->getDirection() == 1 && R1->getJumped() == 0 && R1->acting == 1) {
            int judge = R1->R_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_run_8.png"));
                break;

            }
        }
        if (R1->getDirection() == 2 && R1->getJumped() == 0 && R1->acting == 1) {
            int judge = R1->L_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_run_8.png"));
                break;
            }
        }
        if (R1->getDirection() == 1 && R1->getJumped() == 1 && R1->acting == 1) {
            int judge = R1->R_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/R_jump_6.png"));
                break;
            }
        }
        if (R1->getDirection() == 2 && R1->getJumped() == 1 && R1->acting == 1) {
            int judge = R1->L_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character3/L_jump_6.png"));
                break;
            }
        }

    }
    ///////////////////////////////////////////////////////////
    //                               character 4                                            //
    //////////////////////////////////////////////////////////
    else if (R1->getIdentify() == 4) {

        if (R1->acting == 0) {
            if (R1->getDirection() == 1) {
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_stand.png"));
            }
            else {
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_stand.png"));
            }
        }

        if (R1->getDirection() == 1 && R1->getJumped() == 0 && R1->acting == 1) {
            int judge = R1->R_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_run_8.png"));
                break;

            }
        }
        if (R1->getDirection() == 2 && R1->getJumped() == 0 && R1->acting == 1) {
            int judge = R1->L_run % 8;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_6.png"));
                break;
            case 6:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_7.png"));
                break;
            case 7:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_run_8.png"));
                break;
            }
        }
        if (R1->getDirection() == 1 && R1->getJumped() == 1 && R1->acting == 1) {
            int judge = R1->R_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/R_jump_6.png"));
                break;
            }
        }
        if (R1->getDirection() == 2 && R1->getJumped() == 1 && R1->acting == 1) {
            int judge = R1->L_jump % 6;
            switch (judge)
            {
            case 0:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_jump_1.png"));
                break;
            case 1:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_jump_2.png"));
                break;
            case 2:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_jump_3.png"));
                break;
            case 3:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_jump_4.png"));
                break;
            case 4:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_jump_5.png"));
                break;
            case 5:
                painter1.drawPixmap(R1->getPixelPosition_x(), R1->getPixelPosition_y(), QPixmap("../OOP_Photo/character4/L_jump_6.png"));
                break;
            }
        }

    }



}

void playmode::keyPressEvent(QKeyEvent* k) {
    if (k->key() == Qt::Key_D) {
        R1->setSpeed_x(20);
        R1->setFriction(0);
        R1->setDirection(1);//set role face  right
    }
    if (k->key() == Qt::Key_A) {
        R1->setSpeed_x(-20);
        R1->setFriction(0);
        R1->setDirection(2);//set role face  right
    }
    else if (k->key() == Qt::Key_W) {
        //左下角偵測點
        //右下角偵測點
        int lower_i = (R1->getPixelPosition_y() + R1->getSpeed_y()) / 100;
        int lower_left_j = (R1->getPixelPosition_x() + 30) / 100;
        int lower_right_j = (R1->getPixelPosition_x() + 70) / 100;
        if ((map[lower_i + 1][lower_left_j] >= 1 && map[lower_i + 1][lower_left_j] <= 5) || map[lower_i + 1][lower_right_j] >= 1 && map[lower_i + 1][lower_right_j] <= 5) {
            R1->setSpeed_y(-60);
            R1->setJumped(1);
        }
    }

    k->ignore();
}

void playmode::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case  Qt::Key_A:
        R1->setFriction(5);
        R1->acting = 0;
        break;
    case  Qt::Key_D:
        R1->setFriction(5);
        R1->acting = 0;
        break;
    case Qt::Key_W:
        R1->setJumped(0);
    case  Qt::Key_Q:
        break;
    }
    event->ignore();
}

void playmode::mousePressEvent(QMouseEvent* mouse)
{

    if (mouse->x() >= R1->getPixelPosition_x() && mouse->x() <= R1->getPixelPosition_x() + 150
        && mouse->y() >= R1->getPixelPosition_y() && mouse->y() <= R1->getPixelPosition_y() + 150)
        target = 1;

}

void playmode::mouseReleaseEvent(QMouseEvent* mouse)
{
    switch (target)
    {
    case 1:
        R1->setPixelPosition_x(mouse->x() - 72);
        R1->setPixelPosition_y(mouse->y() - 72);
        break;
    }
    target = 0;
}

void playmode::timerEvent(QTimerEvent* event) {
    update();
}

void playmode::creatEndWidget()
{
    EndWidget* nextwidget = new EndWidget(baseWidget_p);
    baseWidget_p->addWidget(nextwidget);
    baseWidget_p->setCurrentWidget(nextwidget);//jump into next widget ex:EndWidget
}



//====================================================
//                  startWidget
//====================================================



startWidget::startWidget(QStackedWidget* stackedWidget, QWidget* parent)
{
    mciSendString(TEXT("open Jojo.mp3 alias mysong"),
        NULL, 0, NULL);

    mciSendString(TEXT("play mysong"), NULL, 0, NULL);
    time = startTimer(100);
    baseWidget_s = stackedWidget;
    toPlay = new QPushButton("to playmode", this);
    toPlay->setGeometry(-500, -500, 150, 150);
    
}

void startWidget::creatIntroduction()
{
    QT_introduce_screen* nextWidget = new QT_introduce_screen(baseWidget_s);
    baseWidget_s->addWidget(nextWidget);
    baseWidget_s->setCurrentWidget(nextWidget);//jump into next widget ex:EndWidget
}

void startWidget::paintEvent(QPaintEvent* event)
{
    QPixmap pixmapBackground = QPixmap("../OOP_Photo/interface.png");
    QPainter painter(this);
    painter.drawPixmap(this->rect(), pixmapBackground);
    QPainter painter1(this);
    painter1.setRenderHint(QPainter::Antialiasing, true);

}

void startWidget::mousePressEvent(QMouseEvent* mouse)
{
    if (mouse->x() >= 560 && mouse->x() <= 1340 && mouse->y() >= 629 && mouse->y() <= 761)
        creatIntroduction();
}

void startWidget::timerEvent(QTimerEvent* event)
{
    update();
}



//============================================================
//                QT_introduce_screen
//============================================================



QT_introduce_screen::QT_introduce_screen(QStackedWidget* stackedWidget, QWidget* parent)
{
    time = startTimer(100);
    baseWidget_i = stackedWidget;

}
void QT_introduce_screen::paintEvent(QPaintEvent* event)
{
    QPixmap pixmapBackground = QPixmap("../OOP_Photo/introduce.png").scaled(this->size());
    QPainter painter(this);
    painter.drawPixmap(this->rect(), pixmapBackground);
    QPainter painter1(this);
    painter1.setRenderHint(QPainter::Antialiasing, true);

}
void QT_introduce_screen::mousePressEvent(QMouseEvent* mouse)
{
    creatSelectCharactor();
}

void QT_introduce_screen::timerEvent(QTimerEvent* event)
{
    update();
}

void QT_introduce_screen::creatSelectCharactor()
{
    
    QT_select_character* nextWidget = new QT_select_character(baseWidget_i);
    baseWidget_i->addWidget(nextWidget);
    baseWidget_i->setCurrentWidget(nextWidget);//jump into next widget ex:EndWidget
}



//=======================================================
//                  EndWidget
//=======================================================



EndWidget::EndWidget(QStackedWidget* stackedWidget, QWidget* parent)
{
    baseWidget_e = stackedWidget;
    time = startTimer(200);
    
}
void EndWidget::creatStartMode()
{
    mciSendString(TEXT("close mysong"), NULL, 0, NULL);
    startWidget* nextWidget = new startWidget(baseWidget_e);
    baseWidget_e->addWidget(nextWidget);
    baseWidget_e->setCurrentWidget(nextWidget);//jump into next widget ex:EndWidget
}

void EndWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QPixmap pixmapBackground = QPixmap("../OOP_Photo/Winner_screen.png");
    painter.drawPixmap(this->rect(), pixmapBackground);                       //印出背景
                      
    if (winFinal == 1)
    {
        QPixmap pixmapBackground = QPixmap("../OOP_Photo/character_1.png");
        painter.drawPixmap(750, 500, pixmapBackground);
                                                         //1號獲勝
    }
    else if (winFinal == 2)
    {
        QPixmap pixmapBackground = QPixmap("../OOP_Photo/character_2.png");
        painter.drawPixmap(750, 500, pixmapBackground);
                                                         //2號獲勝
    }
    else if (winFinal == 3)
    {
        QPixmap pixmapBackground = QPixmap("../OOP_Photo/character_3.png");
        painter.drawPixmap(750, 500, pixmapBackground);
                                                     //3號獲勝
    }
    else if (winFinal == 4)
    {
        QPixmap pixmapBackground = QPixmap("../OOP_Photo/character_4.png");
        painter.drawPixmap(750, 500, pixmapBackground);
                                                         //4號獲勝
    }
    
}
void EndWidget::mousePressEvent(QMouseEvent* mouse)
{
    if (mouse->x() >= 180 && mouse->x() <= 430 && mouse->y() >= 500 && mouse->y() <= 750)
        target = 1;                             //選擇第一名角色
    else  if (mouse->x() >= 610 && mouse->x() <= 860 && mouse->y() >= 500 && mouse->y() <= 750)
        target = 2;                             //選擇第二名角色
    else  if (mouse->x() >= 1040 && mouse->x() <= 1290 && mouse->y() >= 500 && mouse->y() <= 750)
        target = 3;                             //選擇第三名角色
    else  if (mouse->x() >= 1470 && mouse->x() <= 1720 && mouse->y() >= 500 && mouse->y() <= 750)
        target = 4;                             //選擇第四名角色
    else if (mouse->x() >= 775 && mouse->x() <= 1149 && mouse->y() >= 820 && mouse->y() <= 982)
    {
        if (target > 4)
            creatStartMode();
    }
}

void EndWidget::timerEvent(QTimerEvent* event)
{
    update();
}

//====================================================
//                  select charactor
//====================================================



QT_select_character::QT_select_character(QStackedWidget* stackedWidget, QWidget* parent)
{
    player.port = 8000;
    player.connectToServer();
    time = startTimer(200);
    baseWidget_se = stackedWidget;
    
    number = "1111";
}
void QT_select_character::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QPixmap pixmapBackground = QPixmap("../OOP_Photo/choose_background.png");
    painter.drawPixmap(this->rect(), pixmapBackground);                       //印出背景
    QPixmap people1 = QPixmap("../OOP_Photo/character_1.png");
    painter.drawPixmap(180, 500, people1);                           //印出1號角色
    QPixmap people2 = QPixmap("../OOP_Photo/character_2.png");
    painter.drawPixmap(610, 500, people2);                           //印出2號角色
    QPixmap people3 = QPixmap("../OOP_Photo/character_3.png");
    painter.drawPixmap(1040, 500, people3);                           //印出3號角色
    QPixmap people4 = QPixmap("../OOP_Photo/character_4.png");
    painter.drawPixmap(1470, 500, people4);                           //印出4號角色
    QPixmap correct = QPixmap("../OOP_Photo/correct.png");

    if (number[0] == '0' && number[1] == '0' && number[2] == '0' && number[3] == '0')
        painter.drawPixmap(875, 800, correct);

    number = player.select_ReadMessage();
   
    if (number[0] == "F")
        creatPlayMode();



    if (number[0] == '0')
    {
        QPixmap pixmapBackground = QPixmap("../OOP_Photo/character_5.png");
        painter.drawPixmap(180, 500, pixmapBackground);
    }
    if (number[1] == '0')
    {
        QPixmap pixmapBackground = QPixmap("../OOP_Photo/character_6.png");
        painter.drawPixmap(610, 500, pixmapBackground);
    }
    if (number[2] == '0')
    {
        QPixmap pixmapBackground = QPixmap("../OOP_Photo/character_7.png");
        painter.drawPixmap(1040, 500, pixmapBackground);
    }
    if (number[3] == '0')
    {
        QPixmap pixmapBackground = QPixmap("../OOP_Photo/character_8.png");
        painter.drawPixmap(1470, 500, pixmapBackground);
    }

}
void QT_select_character::mousePressEvent(QMouseEvent* mouse)
{
    QChar temp[4];//the buffer
    for (int i = 0; i < 4; i++)
    {
        temp[i] = number[i];
    }
    for (int i = 0; i < 4; i++)
    {
        number[i] = temp[i];
    }


    QChar send[4];
    
    if (mouse->x() >= 180 && mouse->x() <= 430 && mouse->y() >= 500 && mouse->y() <= 750 && number[0] == '1')
    {
        //選擇第一名角色
        role_choose = 1;
        number[0] = '0';
        player.sendMessage(number);
    }
    else  if (mouse->x() >= 610 && mouse->x() <= 860 && mouse->y() >= 500 && mouse->y() <= 750 && number[1] == '1')
    {
        
        //選擇第二名角色
        role_choose = 2;
        number[1] = '0';
        player.sendMessage(number);
    }
    else  if (mouse->x() >= 1040 && mouse->x() <= 1290 && mouse->y() >= 500 && mouse->y() <= 750 && number[2] == '1')
    {
        
        //選擇第三名角色
        role_choose = 3;
        number[2] = '0';
        player.sendMessage(number);

    }
    else  if (mouse->x() >= 1470 && mouse->x() <= 1720 && mouse->y() >= 500 && mouse->y() <= 750 && number[3] == '1')
    {
         //選擇第四名角色
        role_choose = 4;
        number[3] = '0';
        player.sendMessage(number);

    }
    else if (mouse->x() >= 875 && mouse->x() <= 1000 && mouse->y() >= 800 && mouse->y() <= 925)
    {
        if (number[0] == '0' && number[1] == '0' && number[2] == '0' && number[3] == '0')
        {
            for(int i=0;i<10;i++)
            player.sendMessage(QString("F"));
        }

    }
}
void QT_select_character::timerEvent(QTimerEvent* event)
{
    update();
}
void QT_select_character::creatPlayMode()
{
    player.m_socket->disconnectFromHost();
    player.m_socket->close();
    trapWidget* nextWidget = new trapWidget(baseWidget_se);
    baseWidget_se->addWidget(nextWidget);
    baseWidget_se->setCurrentWidget(nextWidget);//jump into next widget ex:EndWidget
}




//==============================================================
//                        Trap
//==============================================================


trapWidget::trapWidget(QStackedWidget* stackedWidget, QWidget* parent)
{
    player.port = 1234;
    player.connectToServer();
    time = startTimer(100);
    baseWidget_t = stackedWidget;

    spike = new trap(55, 275);

    ice = new trap(305, 275);
    net = new trap(555, 275);
    arch = new trap(430, 275);
    teleport = new trap(180, 275);


}
void trapWidget::paintEvent(QPaintEvent* event)
{

    QPainter painter(this);
    QPixmap pixmapBackground = QPixmap("../OOP_Photo/game_background.png");
    painter.drawPixmap(0, 0, pixmapBackground);
    QPixmap trap_select_area = QPixmap("../OOP_Photo/trap_select_area.png");
    painter.drawPixmap(30, 15, trap_select_area);



    //recieved
    trap_each = player.trap_ReadMessage();

    map[trap_each.x1][trap_each.y1] = trap_each.item1;
    map[trap_each.x2][trap_each.y2] = trap_each.item2;
    if (trap_each.OK_status == 200)
    {
        creatPlayMode();
    }


    painter.drawPixmap(spike->getPosition_x(), spike->getPosition_y(), QPixmap("../OOP_Photo/spike.png"));
    painter.drawPixmap(ice->getPosition_x(), ice->getPosition_y(), QPixmap("../OOP_Photo/ice.png"));
    painter.drawPixmap(net->getPosition_x(), net->getPosition_y(), QPixmap("../OOP_Photo/net.png"));
    painter.drawPixmap(arch->getPosition_x(), arch->getPosition_y(), QPixmap("../OOP_Photo/rocketstand.png"));
    painter.drawPixmap(teleport->getPosition_x(), teleport->getPosition_y(), QPixmap("../OOP_Photo/teleport.png"));

    if (token == 0)
    {
        QPixmap correct = QPixmap("../OOP_Photo/correct.png");
        painter.drawPixmap(1750, 50, correct);
    }
    if (flag == true)
    {
        QPixmap clicked = QPixmap("../OOP_Photo/correct_red.png");
        painter.drawPixmap(1750, 50, clicked);
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (map[i][j] == 1)
            {
                painter.drawPixmap(j * 100, i * 100, QPixmap("../OOP_Photo/brick.png").scaled(100, 100));
            }
            else if (map[i][j] == 2)
            {
                painter.drawPixmap(j * 100, i * 100, QPixmap("../OOP_Photo/spike.png"));
            }
            else if (map[i][j] == 3)
            {
                painter.drawPixmap(j * 100, i * 100, QPixmap("../OOP_Photo/ice.png"));
            }
            else if (map[i][j] == 4)
            {
                painter.drawPixmap(j * 100, i * 100, QPixmap("../OOP_Photo/net.png"));
            }
            else if (map[i][j] == 5)
            {
                painter.drawPixmap(j * 100, i * 100, QPixmap("../OOP_Photo/rocketstand.png"));
            }
            else if (map[i][j] == 6)
            {
                painter.drawPixmap(j * 100, i * 100, QPixmap("../OOP_Photo/teleport.png"));
            }
        }
    }

}

//creatPlayMode();


void trapWidget::timerEvent(QTimerEvent* event)
{
    update();
}

void trapWidget::creatPlayMode()
{
    player.m_socket->disconnectFromHost();
    player.m_socket->close();
    playmode* nextWidget = new playmode(baseWidget_t);
    baseWidget_t->addWidget(nextWidget);
    baseWidget_t->setCurrentWidget(nextWidget);//jump into next widget ex:EndWidget
}

void trapWidget::mousePressEvent(QMouseEvent* mouse)
{
    if (mouse->x() >= 1750 && mouse->x() <= 1875 && mouse->y() >= 50 && mouse->y() <= 175)
    {
        flag = true;
        changeMap_send();//to server
    }

    //trap 2~6
    if (mouse->x() >= spike->getPosition_x() &&
        mouse->x() <= spike->getPosition_x() + 100
        && mouse->y() >= spike->getPosition_y() &&
        mouse->y() <= spike->getPosition_y() + 100)
    {
        target = 2;
    }

    else if (mouse->x() >= ice->getPosition_x() &&
        mouse->x() <= ice->getPosition_x() + 100
        && mouse->y() >= ice->getPosition_y() &&
        mouse->y() <= ice->getPosition_y() + 100)
    {
        target = 3;
    }
    else if (mouse->x() >= net->getPosition_x() &&
        mouse->x() <= net->getPosition_x() + 100
        && mouse->y() >= net->getPosition_y() &&
        mouse->y() <= net->getPosition_y() + 100)
    {
        target = 4;
    }
    else if (mouse->x() >= arch->getPosition_x() &&
        mouse->x() <= arch->getPosition_x() + 100
        && mouse->y() >= arch->getPosition_y() &&
        mouse->y() <= arch->getPosition_y() + 100)
    {
        target = 5;
    }
    else if (mouse->x() >= teleport->getPosition_x() &&
        mouse->x() <= teleport->getPosition_x() + 100
        && mouse->y() >= teleport->getPosition_y() &&
        mouse->y() <= teleport->getPosition_y() + 100)
    {
        target = 6;
    }
}

void trapWidget::mouseReleaseEvent(QMouseEvent* mouse)
{
    if (mouse->x() >= 30 && mouse->x() <= 680 && mouse->y() >= 15 && mouse->y() <= 415)
    {
        switch (target)//放回去
        {
        case 2:
            if (choose_2 == true)
                token++;
            choose_2 = false;
            spike->setPosition_x(55);
            spike->setPosition_y(275);


            break;
        case 3:

            if (choose_3 == true)
                token++;
            choose_3 = false;
            ice->setPosition_x(305);
            ice->setPosition_y(275);


            break;
        case 4:

            if (choose_4 == true)
                token++;
            choose_4 = false;
            net->setPosition_x(555);
            net->setPosition_y(275);


            break;
        case 5:

            if (choose_5 == true)
                token++;
            choose_5 = false;
            arch->setPosition_x(430);
            arch->setPosition_y(275);


            break;

        case 6:
            if (choose_6 == true)
                token++;
            choose_6 = false;
            teleport->setPosition_x(180);
            teleport->setPosition_y(275);


            break;
        }
        target = 0;


    }
    else//放下去
    {
        switch (target)
        {
        case 2:
            if (choose_2 == true || token > 0)
            {
                if (choose_2 == false)
                    token--;
                choose_2 = true;
                spike->setPosition_x(mouse->x() - 50);
                spike->setPosition_y(mouse->y() - 50);

            }
            break;
        case 3:
            if (choose_3 == true || token > 0)
            {
                if (choose_3 == false)
                    token--;
                choose_3 = true;
                ice->setPosition_x(mouse->x() - 50);
                ice->setPosition_y(mouse->y() - 50);
            }
            break;
        case 4:
            if (choose_4 == true || token > 0)
            {
                if (choose_4 == false)
                    token--;
                choose_4 = true;
                net->setPosition_x(mouse->x() - 50);
                net->setPosition_y(mouse->y() - 50);
            }
            break;
        case 5:
            if (choose_5 == true || token > 0)
            {
                if (choose_5 == false)
                    token--;
                choose_5 = true;
                arch->setPosition_x(mouse->x() - 50);
                arch->setPosition_y(mouse->y() - 50);

            }
            break;

        case 6:
            if (choose_6 == true || token > 0)
            {
                if (choose_6 == false)
                    token--;
                choose_6 = true;
                teleport->setPosition_x(mouse->x() - 50);
                teleport->setPosition_y(mouse->y() - 50);

            }
            break;
        }
    }
    target = 0;

}

void trapWidget::changeMap_send()
{

    int que = 1;
    int re_map_x = 0;
    int re_map_y = 0;
    if (choose_2 == true)
    {
        re_map_x = (spike->getPosition_y() + 50) / 100;//x,y有互換
        re_map_y = (spike->getPosition_x() + 50) / 100;
        if (que == 1)
        {
            trap_each.item1 = 2;
            trap_each.x1 = re_map_x;
            trap_each.y1 = re_map_y;
            que += 1;
        }
        else if (que == 2)
        {
            trap_each.item2 = 2;
            trap_each.x2 = re_map_x;
            trap_each.y2 = re_map_y;
            que += 1;
        }
    }
    if (choose_3 == true)
    {
        re_map_x = (ice->getPosition_y() + 50) / 100;//x,y有互換
        re_map_y = (ice->getPosition_x() + 50) / 100;
        if (que == 1)
        {
            trap_each.item1 = 3;
            trap_each.x1 = re_map_x;
            trap_each.y1 = re_map_y;
            que += 1;
        }
        else if (que == 2)
        {
            trap_each.item2 = 3;
            trap_each.x2 = re_map_x;
            trap_each.y2 = re_map_y;
            que += 1;
        }
    }
    if (choose_4 == true)
    {
        re_map_x = (net->getPosition_y() + 50) / 100;//x,y有互換
        re_map_y = (net->getPosition_x() + 50) / 100;
        if (que == 1)
        {
            trap_each.item1 = 4;
            trap_each.x1 = re_map_x;
            trap_each.y1 = re_map_y;
            que += 1;
        }
        else if (que == 2)
        {
            trap_each.item2 = 4;
            trap_each.x2 = re_map_x;
            trap_each.y2 = re_map_y;
            que += 1;
        }
    }
    if (choose_5 == true)
    {
        re_map_x = (arch->getPosition_y() + 50) / 100;//x,y有互換
        re_map_y = (arch->getPosition_x() + 50) / 100;
        if (que == 1)
        {
            trap_each.item1 = 5;
            trap_each.x1 = re_map_x;
            trap_each.y1 = re_map_y;
            que += 1;
        }
        else  if (que == 2)
        {
            trap_each.item2 = 5;
            trap_each.x2 = re_map_x;
            trap_each.y2 = re_map_y;
            que += 1;
        }
    }
    if (choose_6 == true)
    {
        re_map_x = (teleport->getPosition_y() + 50) / 100;//x,y有互換
        re_map_y = (teleport->getPosition_x() + 50) / 100;
        if (que == 1)
        {
            trap_each.item1 = 6;
            trap_each.x1 = re_map_x;
            trap_each.y1 = re_map_y;
            que += 1;
        }
        else if (que == 2)
        {
            trap_each.item2 = 6;
            trap_each.x2 = re_map_x;
            trap_each.y2 = re_map_y;
            que += 1;
        }
    }


    player.sendMessage(trap_each);

}