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
	HANDLE thread[2]; //用于存储线程句柄
	DWORD  dwThreadID[3]; //用于存储线程的ID  
	SellThreadPara para[2]; //传递给线程处理函数的参数
	int remainNum = 0;

	void createThread();
	bool VerifyNumber(QString);

	QTimer *timer;
};
