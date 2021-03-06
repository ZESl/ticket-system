#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ticketsystem.h"

class ticketsystem : public QMainWindow
{
    Q_OBJECT

public:
    ticketsystem(QWidget *parent = Q_NULLPTR);


private slots:
	void on_pushButton_clicked();

private:
    Ui::ticketsystemClass ui;

	void createThread();
	void initialCriticalSection();
	void enterCriticalSection();
	void leaveCriticalSection();
};
