#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui.h"
#include <qmessagebox>
#include "qtvmodel.h"

class gui : public QMainWindow
{
    Q_OBJECT

public:
    gui();

private:
    Ui::guiClass ui;
    CAPI api;
    Curves curves;
    QMessageBox error_mb;
    QTVModel model;

private slots:
    void populate();
};
