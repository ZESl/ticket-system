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
		initialCriticalSection();
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

DWORD WINAPI SellTicketThreadProc(__in LPVOID lpParameter)
{
	// enterCriticalSection
	::EnterCriticalSection(&cs);
	if (winPara.biz->GetBalanceNum > 0) {
		int ticketno = winPara.biz->GetRandTicket;

		QFile myfile("ticket.txt");//����һ������ļ����ĵ�
		if (myfile.open(QFile::WriteOnly | QFile::Truncate))//ע��WriteOnly�����ı���д���ʱ���ã�ReadOnly���ڶ��ı������ݵ�ʱ���ã�Truncate��ʾ��ԭ���ļ��е��������
		{
			//��ȡ֮ǰsetPlainText������
			QTextStream out(&myfile);
			out << "No." << winPara.win_no << " window has sold a ticket: " << ticketno << "." << endl;
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


	thread[0] = ::CreateThread(NULL, 0, SellTicketThreadProc, NULL, 0, NULL);
	thread[1] = ::CreateThread(NULL, 0, SellTicketThreadProc, NULL, 0, NULL);
}

void ticketsystem::initialCriticalSection()
{
	
}

void ticketsystem::onTimer()
{
}
