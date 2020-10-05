#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ticketsystem.h"
#include "CTicketBiz.h"

struct SellThread {
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

private slots:
	void on_pushButton_clicked();	//start selling ticket

private:
    Ui::ticketsystemClass ui;
	
	SellThread thread1;
	SellThread thread2;
	CRITICAL_SECTION g_csTicket;

	void SellTicketThreadProc();
	void createThread();
	void initialCriticalSection();
	void enterCriticalSection(SellThreadParam);
	void leaveCriticalSection(SellThreadParam);
	void onTimer();	//update the interface

	bool VerifyNumber(QString);
	
};
