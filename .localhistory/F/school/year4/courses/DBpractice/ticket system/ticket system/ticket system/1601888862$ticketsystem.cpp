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

	SellThreadPara*Info = (SellThreadPara*)lpParameter;
	if (Info->biz->GetBalanceNum > 0) {
		int ticketno = Info->biz->GetRandTicket;

		QFile myfile("ticket.txt");
		if (myfile.open(QFile::WriteOnly | QFile::Truncate))//注意WriteOnly是往文本中写入的时候用，ReadOnly是在读文本中内容的时候用，Truncate表示将原来文件中的内容清空
		{
			//读取之前setPlainText的内容
			QTextStream out(&myfile);
			out << "No." << Info->win_no << " window has sold a ticket: " << ticketno << "." << endl;
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
	
	// set para
	para[0].biz = para[1].biz = bizTmp;
	para[0].service = para[1].service = false;
	para[0].wndShow = ui.textBrowser;
	para[1].wndShow = ui.textBrowser_2;
	para[0].win_no = 1;
	para[1].win_no = 2;

	for (int i = 0; i < 2; i++)
	{
		thread[i] = CreateThread(NULL, 0, SellTicketThreadProc, &para[i], 0, &dwThreadID[i]);
	}
}

void ticketsystem::onTimer()
{
}
