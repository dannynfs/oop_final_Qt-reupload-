#pragma comment(lib,"WINMM.LIB")


#include <QtWidgets/QMainWindow>

#include <QApplication>
#include <QPushButton>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QtWidgets/QWidget>
#include <QSize>
#include <QApplication>
#include <QtGui>
#include <QMouseEvent>

//#include "ui__qt_merge1.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <QtWidgets/QWidget>
#include "client.h"
#include "arch.h"

#include <mmsystem.h>
#include <windows.h>

struct trap;
struct Role;
class oop_final_project_20210105 : public QMainWindow
{
	Q_OBJECT
public:
	oop_final_project_20210105(QWidget* parent = Q_NULLPTR);
private:
	QStackedWidget* stack;
};

class QbaseWidget :QWidget
{
	Q_OBJECT
public:
	//	QbaseWidget(QWidget* parent = Q_NULLPTR)
protected:
	QStackedWidget* baseWidget;

};


class playmode :public QWidget
{
	Q_OBJECT
public:
	playmode(QStackedWidget* stackedWidget, QWidget* parent = Q_NULLPTR);
	void paintEvent(QPaintEvent*);
	void timerEvent(QTimerEvent*);
	void keyPressEvent(QKeyEvent*);
	void keyReleaseEvent(QKeyEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);

public slots:
	void creatEndWidget();
protected:
	QStackedWidget* baseWidget_p;
	QPushButton* toEnd;//no use but dont delete(unknown bug)
	Role* R1;
	Role* other_1;
	Role* other_2;
	Role* other_3;
	Role* other_4;

	arch* Arch[4];

	client player;
	int time;

	int target = 0;
	int arch_num;


	SendStruct Sendpos;
	SendStruct recpos;
	recv_Struct package;
};


class startWidget :public QWidget
{
	Q_OBJECT
public:
	startWidget(QStackedWidget* stackedWidget, QWidget* parent = Q_NULLPTR);
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent*);
	void timerEvent(QTimerEvent*);
public slots:
	void creatIntroduction();
protected:
	QStackedWidget* baseWidget_s;
	QPushButton* toPlay;//no use but dont delete(unknown bug)
	int time;
	int target = 0;
};

class QT_introduce_screen : public QWidget
{
	Q_OBJECT
public:
	QT_introduce_screen(QStackedWidget*, QWidget* parent = Q_NULLPTR);
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent*);
	void timerEvent(QTimerEvent*);
public slots:
	void creatSelectCharactor();
private:
	//   Ui::QT_start_screenClass ui;
	int time;
	int target = 0;
	QStackedWidget* baseWidget_i;
};

class EndWidget :public QWidget
{
	Q_OBJECT
public:
	EndWidget(QStackedWidget* stackedWidget, QWidget* parent = Q_NULLPTR);
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent*);
	void timerEvent(QTimerEvent*);
public slots:
	void creatStartMode();
protected:
	QStackedWidget* baseWidget_e;
	QPushButton* toStart;
	int target = 0;
	int time;
};

class QT_select_character : public QWidget
{
	Q_OBJECT

public:

	QT_select_character(QStackedWidget*, QWidget* parent = Q_NULLPTR);
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent*);
	void timerEvent(QTimerEvent*);
public slots:
	void creatPlayMode();
private:
	//   Ui::QT_select_characterClass ui;

	int target = 0;
	int time;
	QStackedWidget* baseWidget_se;
	QPushButton* toStart;
	QString number;
	client player;

};

class trapWidget :public QWidget
{
	Q_OBJECT
public:
	trapWidget(QStackedWidget* stackedWidget, QWidget* parent = Q_NULLPTR);
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void timerEvent(QTimerEvent*);
	void changeMap_send();//°e§ï¦a¹Ïconcept
public slots:
	void creatPlayMode();
protected:
	QStackedWidget* baseWidget_t;
	QPushButton* toStart;
	int target = 0;
	int time;

	trap* spike;// (55, 275);//2
	trap* ice;// (305, 275);//3
	trap* net;// (555, 275);//4
	trap* arch;// (430, 275);//5
	trap* teleport;// (180, 275);//6

	trap* spike2;// (55, 275);//2
	trap* ice2;// (305, 275);//3
	trap* net2;// (555, 275);//4
	trap* arch2;// (430, 275);//5
	trap* teleport2;// (180, 275);//6

	trap* spike3;// (55, 275);//2
	trap* ice3;// (305, 275);//3
	trap* net3;// (555, 275);//4
	trap* arch3;// (430, 275);//5
	trap* teleport3;// (180, 275);//6

	trap* spike4;// (55, 275);//2
	trap* ice4;// (305, 275);//3
	trap* net4;// (555, 275);//4
	trap* arch4;// (430, 275);//5
	trap* teleport4;// (180, 275);//6





	int token = 2;
	bool choose_2 = false;
	bool choose_3 = false;
	bool choose_4 = false;
	bool choose_5 = false;
	bool choose_6 = false;
	bool check = false;

	trapStruct trap_each;
	client player;
};