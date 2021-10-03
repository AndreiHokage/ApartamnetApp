#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ApartamnetApp.h"

class ApartamnetApp : public QMainWindow
{
    Q_OBJECT

public:
    ApartamnetApp(QWidget *parent = Q_NULLPTR);

private:
    Ui::ApartamnetAppClass ui;
};
