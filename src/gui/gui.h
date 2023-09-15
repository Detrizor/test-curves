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
    CurvesData m_vSecondContainer;
    QMessageBox error_mb;
    QTVModel model;
    QTVModelSecond m_ModelSecond;

    float Param() const;
    void ResetSecondContainer();

private slots:
    void populate();
    void calculate();
    void PopulateSecondContainer();
    void SortSecondContainer();
    void ComputeSecondContainer();
};
