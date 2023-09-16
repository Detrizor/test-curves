#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui.h"
#include <qmessagebox>
#include "qtvmodel.h"
#include "compute_object.h"
#include "qthread.h"

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
    std::vector<std::unique_ptr<QThread>> m_vThreads;
    std::vector<std::unique_ptr<CComputeObject>> m_vComputeObjects;
    double m_fSecondContainerSum;

    float Param() const;
    void ResetSecondContainer();
    void SetupThreads();

public:
    void SetupComputeInterval(CurvesData::iterator& begin, CurvesData::iterator& end, int thread_num);
    void AddSecondContainerSum(double val);

private slots:
    void populate();
    void calculate();
    void PopulateSecondContainer();
    void SortSecondContainer();
    void ComputeSecondContainer();
    void UpdateComputeResult();
};
