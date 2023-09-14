#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui.h"
#include "api.h"

class gui : public QMainWindow
{
    Q_OBJECT

public:
    gui(QWidget *parent = nullptr);

private:
    Ui::guiClass ui;
    std::unique_ptr<CAPI> pApi;
};
