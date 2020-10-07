#include "ticketsystem.h"
#include <QDebug>
#include <QTimer>
#include <QDateTime>

CRITICAL_SECTION cs;

ticketsystem::ticketsystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	// set a timer
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));

	InitializeCriticalSection(&cs);
}

void ticketsystem::on_pushButton_clicked()
{
	// clear the log file
	QFile myfile("ticket.txt");
	if (myfile.open(QFile::WriteOnly | QIODevice::Truncate))
	{
		QTextStream out(&myfile);
		out << "" << endl;
	}

	// clear the text browsers
	ui.textBrowser->setText("");
	ui.textBrowser_2->setText("");

	// check if is integer
	QString totalNumText = ui.lineEdit->text();
	if (VerifyNumber(totalNumText) && totalNumText.toInt()>0) {
		// start the timer
		timer->start(200);
		// start the program
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

DWORD WINAPI SellTicketThreadProc(LPVOID lpParameter)
{
	SellThreadPara*Info = (SellThreadPara*) lpParameter;
	
	while (Info->biz->GetBalanceNum() > 0 && Info->service) {
		// enterCriticalSection
		::EnterCriticalSection(&cs);

		if (Info->biz->GetBalanceNum() > 0) {
			int ticketno = Info->biz->GetRandTicket();
			QDateTime current_date_time = QDateTime::currentDateTime();
			QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");

			QString str = "No.";
			str.append(QString::number(Info->win_no));
			str.append(" window has sold a ticket: ");
			str.append(QString::number(ticketno));
			str.append("  ***  ");
			str.append(current_date);		//附加系统时间
			str.append(".\n");

			qDebug() << str;

			Info->wndShow->append(str);

			// save log file
			QFile myfile("ticket.txt");
			if (myfile.open(QFile::WriteOnly | QIODevice::Append))
			{
				QTextStream out(&myfile);
				out << str << endl;
			}
		}
		else {
			Info->service = false;
		}

		// leaveCriticalSection
		::LeaveCriticalSection(&cs);
		Sleep(1000);
	}
	
	return 0;
}

void ticketsystem::createThread()
{
	QString totalNumText = ui.lineEdit->text();
	int totalNum = totalNumText.toInt();
	
	// set para
	para[0].biz = para[1].biz = new CTicketBiz(totalNum);
	para[0].service = para[1].service = true;
	para[0].wndShow = ui.textBrowser;
	para[1].wndShow = ui.textBrowser_2;
	para[0].win_no = 1;
	para[1].win_no = 2;

	for (int i = 0; i < 2; i++)
	{
		thread[i] = CreateThread(NULL, 0, SellTicketThreadProc, &para[i], 0, NULL);
	}
}

void ticketsystem::handleTimeout()
{
	ui.label_3->setText(QString::number(para[0].biz->GetBalanceNum()));
	ui.label_3->update();
}
