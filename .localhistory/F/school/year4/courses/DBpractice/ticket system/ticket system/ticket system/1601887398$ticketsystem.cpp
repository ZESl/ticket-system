#include "ticketsystem.h"


CRITICAL_SECTION cs;

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

DWORD WINAPI SellTicketThreadProc(__in LPVOID lpParameter)
{
	// enterCriticalSection
	::EnterCriticalSection(&cs);
	if (win.biz->GetBalanceNum > 0) {
		int ticketno = win.biz->GetRandTicket;

		QFile myfile("ticket.txt");//创建一个输出文件的文档
		if (myfile.open(QFile::WriteOnly | QFile::Truncate))//注意WriteOnly是往文本中写入的时候用，ReadOnly是在读文本中内容的时候用，Truncate表示将原来文件中的内容清空
		{
			//读取之前setPlainText的内容
			QTextStream out(&myfile);
			out << "No." << win.win_no << " window has sold a ticket: " << ticketno << "." << endl;
		}
	}
	// leaveCriticalSection
	::LeaveCriticalSection(&cs);
}

void ticketsystem::createThread()
{
	QString totalNumText = ui.lineEdit->text();
	int totalNum = totalNumText.toInt();
	CTicketBiz* bizTmp = new CTicketBiz(totalNum);
	
	// set up window
	win.biz = bizTmp;
	win.wndShow = ui.textBrowser;
	win.win_no = 1;
	win.service = false;

	thread1 = ::CreateThread(NULL, 0, SellTicketThreadProc, NULL, 0, NULL);
	thread2 = ::CreateThread(NULL, 0, SellTicketThreadProc, NULL, 0, NULL);
}

void ticketsystem::initialCriticalSection()
{
	
}

void ticketsystem::onTimer()
{
}
