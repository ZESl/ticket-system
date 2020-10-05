#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ticketsystem.h"
#include "CTicketBiz.h"

class ticketsystem : public QMainWindow
{
    Q_OBJECT

public:
    ticketsystem(QWidget *parent = Q_NULLPTR);

private slots:
	//void on_pushButton_clicked();	//start selling ticket

private:
    Ui::ticketsystemClass ui;
	struct SellThreadParam {
		CTicketBiz* biz;
		// CListBox* wndShow; // Point to the ticket window
		int win_no; // Ticket window number
		bool service; // Ticket sale status
	};

	void createThread();
	void initialCriticalSection();
	void enterCriticalSection();
	void leaveCriticalSection();
	void onTimer();	//update the interface
};
