#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ticketsystem.h"

class ticketsystem : public QMainWindow
{
    Q_OBJECT

public:
    ticketsystem(QWidget *parent = Q_NULLPTR);

private:
    Ui::ticketsystemClass ui;
};
