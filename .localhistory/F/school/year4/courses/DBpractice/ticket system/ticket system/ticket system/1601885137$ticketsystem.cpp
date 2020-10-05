#include "ticketsystem.h"
#include "qmessagebox.h"
#include "qfile.h"
#include "qtextstream.h"

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
		SellTicketThreadProc();
	}
	else {
		QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("请输入一个大于零的整数"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
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
	createThread();
	initialCriticalSection();
}

void ticketsystem::createThread()
{
	QString totalNumText = ui.lineEdit->text();
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

void ticketsystem::initialCriticalSection()
{
}

void ticketsystem::enterCriticalSection(SellThreadParam win)
{
	if (win.biz->GetBalanceNum > 0) {
		int ticketno = win.biz->GetRandTicket;

		QFile myfile("ticket.txt");//创建一个输出文件的文档
		if (myfile.open(QFile::WriteOnly | QFile::Truncate))//注意WriteOnly是往文本中写入的时候用，ReadOnly是在读文本中内容的时候用，Truncate表示将原来文件中的内容清空
		{
			//读取之前setPlainText的内容
			QTextStream out(&myfile);
			out << "No." << win.win_no << " window has sold a ticket: " << ticketno << "." <<endl;
		}
	}
	leaveCriticalSection(win);
}

void ticketsystem::leaveCriticalSection(SellThreadParam win)
{
	win.service = false;
}

void ticketsystem::onTimer()
{
}
