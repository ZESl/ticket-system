#include "ticketsystem.h"
#include "qmessagebox.h"

ticketsystem::ticketsystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void ticketsystem::on_pushButton_clicked()
{
	// initialize
	QString totalNumText = ui.lineEdit->text;
	if (VerifyNumber(totalNumText)) {
		int totalNum = totalNumText.toInt();
		int *pTicket;	// Point to the array that saves the ticket information
		pTicket = new int[totalNum];
		for (int i = 0; i < totalNum; i++) {
			pTicket[i] = 1;
		}
		// set up window1
		win1.biz = new CTicketBiz(pTicket, totalNum);
		win1.wndShow = ui.textBrowser;
		win1.win_no = 1;
		win1.service = false;
		// set up window2
		win2.biz = new CTicketBiz(pTicket, totalNum);
		win2.wndShow = ui.textBrowser_2;
		win2.win_no = 2;
		win2.service = false;
	}
	else {
		QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("请输入一个大于零的整数"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}
}
bool VerifyNumber(QString str)
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

void ticketsystem::createThread()
{
	
}

void ticketsystem::initialCriticalSection()
{
}

void ticketsystem::enterCriticalSection()
{
}

void ticketsystem::leaveCriticalSection()
{
}

void ticketsystem::onTimer()
{
}
