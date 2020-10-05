#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ticketsystem.h"
#include "CTicketBiz.h"
#include "qmessagebox.h"
#include "qfile.h"
#include "qtextstream.h" 
#include <Windows.h>    


class ticketsystem : public QMainWindow
{
    Q_OBJECT

public:
    ticketsystem(QWidget *parent = Q_NULLPTR);

private slots:
	void on_pushButton_clicked();	//start selling ticket

private:
	struct SellThreadPara {
		CTicketBiz* biz;
		QTextBrowser* wndShow; // Point to the ticket window
		int win_no; // Ticket window number
		bool service; // Ticket sale status
	};

    Ui::ticketsystemClass ui;
	HANDLE thread[2]; //���ڴ洢�߳̾��
	DWORD  dwThreadID[3]; //���ڴ洢�̵߳�ID  
	SellThreadPara para[2]; //���ݸ��̴߳������Ĳ���

	void createThread();
	void onTimer();	//update the interface
	bool VerifyNumber(QString);
};
