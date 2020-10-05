#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ticketsystem.h"
#include "CTicketBiz.h"
#include "qmessagebox.h"
#include "qfile.h"
#include "qtextstream.h" 
#include <Windows.h>    

struct SellThreadPara {
	CTicketBiz* biz;
	QTextBrowser* wndShow; // Point to the ticket window
	int win_no; // Ticket window number
	bool service; // Ticket sale status
};

class ticketsystem : public QMainWindow
{
    Q_OBJECT

public:
    ticketsystem(QWidget *parent = Q_NULLPTR);

public slots:
	void handleTimeout();

private slots:
	void on_pushButton_clicked();	//start selling ticket

private:
    Ui::ticketsystemClass ui;

	// thread related
	HANDLE thread[2];
	SellThreadPara para[2]; // 传递给线程处理函数的参数

	QTimer *timer;	//timer update the interface every 0.2s
	int remainNum = 0;	// # remaining tickets

	void createThread();
	bool VerifyNumber(QString);
};
