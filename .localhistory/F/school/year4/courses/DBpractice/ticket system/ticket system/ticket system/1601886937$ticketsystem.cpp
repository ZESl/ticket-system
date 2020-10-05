#include "ticketsystem.h"
#include "qmessagebox.h"
#include "qfile.h"
#include "qtextstream.h"

#include "stdafx.h"  
#include <Windows.h>    

CRITICAL_SECTION g_csTicket;

ticketsystem::ticketsystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void ticketsystem::on_pushButton_clicked()
{
	// initialize
	QString totalNumText = ui.lineEdit->text();
	if (VerifyNumber(totalNumText) && totalNumText.toInt()>0) {
		//start the program
		initialCriticalSection();
		createThread();
		SellTicketThreadProc();
	}
	else {
		QMessageBox::warning(NULL, QStringLiteral("����"), QStringLiteral("������һ�������������"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		ui.lineEdit->setText("");
	}
}
bool ticketsystem::VerifyNumber(QString str)
{
	std::string temp = str.toStdString();
	for (int i = 0; i < str.length(); i++)
	{
		if (temp[i]<'0' || temp[i]>'9')
		{
			return false;
		}
	}
	return true;
}

void ticketsystem::SellTicketThreadProc()
{
	while (win.biz->GetBalanceNum > 0 && !win.service) {
		win.service = true;
		// enterCriticalSection
		enterCriticalSection(win);
		if (win.biz->GetBalanceNum > 0) {
			int ticketno = win.biz->GetRandTicket;

			QFile myfile("ticket.txt");//����һ������ļ����ĵ�
			if (myfile.open(QFile::WriteOnly | QFile::Truncate))//ע��WriteOnly�����ı���д���ʱ���ã�ReadOnly���ڶ��ı������ݵ�ʱ���ã�Truncate��ʾ��ԭ���ļ��е��������
			{
				//��ȡ֮ǰsetPlainText������
				QTextStream out(&myfile);
				out << "No." << win.win_no << " window has sold a ticket: " << ticketno << "." << endl;
			}
		}
		// leaveCriticalSection
		leaveCriticalSection(win);
	}
}

void ticketsystem::createThread()
{
	QString totalNumText = ui.lineEdit->text();
	int totalNum = totalNumText.toInt();
	CTicketBiz* bizTmp = new CTicketBiz(totalNum);
	
	// set up window
	thread1.biz = bizTmp;
	thread1.wndShow = ui.textBrowser;
	thread1.win_no = 1;
	thread1.service = false;

	thread1.biz = bizTmp;
	thread1.wndShow = ui.textBrowser_2;
	thread1.win_no = 2;
	thread1.service = false;
}

void ticketsystem::initialCriticalSection()
{
	
}

void ticketsystem::enterCriticalSection(SellThread win)
{
	win.service = true;
}

void ticketsystem::leaveCriticalSection(SellThread win)
{
	win.service = false;
}

void ticketsystem::onTimer()
{
}
