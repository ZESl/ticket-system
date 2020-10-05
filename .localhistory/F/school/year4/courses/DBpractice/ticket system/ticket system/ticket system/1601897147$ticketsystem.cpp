#include "ticketsystem.h"

CRITICAL_SECTION cs;

ticketsystem::ticketsystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	InitializeCriticalSection(&cs);
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

DWORD WINAPI SellTicketThreadProc(LPVOID lpParameter)
{
	// enterCriticalSection
	::EnterCriticalSection(&cs);

	SellThreadPara*Info = (SellThreadPara*) lpParameter;
	if (Info->biz->GetBalanceNum() > 0) {
		int ticketno = Info->biz->GetRandTicket();
		
		QString str = "No." + Info->win_no;
		str.append(" window has sold a ticket: " + ticketno);
		str.append(".\n");

		Info->wndShow->append(str);

		// ����log file
		QFile myfile("ticket.txt");
		if (myfile.open(QFile::WriteOnly | QFile::Truncate))//ע��WriteOnly�����ı���д���ʱ���ã�ReadOnly���ڶ��ı������ݵ�ʱ���ã�Truncate��ʾ��ԭ���ļ��е��������
		{
			//��ȡ֮ǰsetPlainText������
			QTextStream out(&myfile);
			out << str << endl;
		}
	}
	// leaveCriticalSection
	::LeaveCriticalSection(&cs);
	return 0;
}

void ticketsystem::createThread()
{
	QString totalNumText = ui.lineEdit->text();
	int totalNum = totalNumText.toInt();
	
	// set para
	para[0].biz = para[1].biz = new CTicketBiz(totalNum);
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
