#include "gui.h"

gui::gui() : error_mb(this), model(curves), m_ModelSecond(m_vSecondContainer)
{
    ui.setupUi(this);
    error_mb.setText("Failed to load curves.dll!");
    ui.tvObjects->setModel(&model);
    ui.tvObjects->setColumnWidth(0, 50);
    ui.tvObjects->setColumnWidth(1, 100);
    ui.tvObjects->setColumnWidth(2, 100);
    ui.tvObjects->setColumnWidth(3, 300);
    ui.tvObjects->setColumnWidth(4, 300);
    ui.tvObjects_2->setModel(&m_ModelSecond);
}

void gui::populate()
{
    if (!api.Loaded())
    {
        error_mb.show();
        return;
    }

    if (curves.size())
    {
        curves.clear();
        model.reset();
        ResetSecondContainer();
    }

    if (unsigned cnt = ui.edtObjectsNum->text().toInt())
    {
        for (unsigned i = 0; i < cnt; i++)
            curves.push_back(api.CreateCurve());
        model.update(cnt, Param());
    }
}

float gui::Param() const
{
    float res = ui.edtParam->text().toFloat();
    if (ui.cbPI->isChecked())
        res *= PI;
    return res;
}

void gui::calculate()
{
    model.reset();
    unsigned cnt = ui.edtObjectsNum->text().toInt();
    model.update(cnt, Param());
}

void gui::PopulateSecondContainer()
{
    ResetSecondContainer();

    for (const auto& I : curves)
    {
        if (!strcmp(I->Type(), "Circle"))
            m_vSecondContainer.push_back(I.get());
    }
    m_ModelSecond.update(m_vSecondContainer.size());
}

void gui::SortSecondContainer()
{
    struct SmallerRadius
    {
        bool operator()(const DLL_Pure* l, const DLL_Pure* r) const
        {
            return l->R1() < r->R1();
        }
    };

    m_ModelSecond.reset();
    std::sort(m_vSecondContainer.begin(), m_vSecondContainer.end(), SmallerRadius());
    m_ModelSecond.update(m_vSecondContainer.size());
}

void gui::ResetSecondContainer()
{
    if (m_vSecondContainer.size())
    {
        m_vSecondContainer.clear();
        m_ModelSecond.reset();
    }
    ui.edtSum->setText("");
}

void gui::SetupThreads()
{
    for (int i = 0, threads = std::thread::hardware_concurrency(); i < threads; i++)
    {
        m_vThreads.push_back(std::make_unique<QThread>());
        m_vComputeObjects.push_back(std::make_unique<CComputeObject>());
        connect(m_vThreads.back().get(), &QThread::started, m_vComputeObjects.back().get(), &CComputeObject::Start);
        connect(m_vComputeObjects.back().get(), &CComputeObject::Finished, m_vThreads.back().get(), &QThread::terminate);
        connect(m_vComputeObjects.back().get(), &CComputeObject::Finished, this, &gui::UpdateComputeResult);
        m_vComputeObjects.back()->SetThreadNum(i);
        m_vComputeObjects.back()->moveToThread(m_vThreads.back().get());
    }
    CComputeObject::SetGui(this);
}

void gui::ComputeSecondContainer()
{
    m_fSecondContainerSum = 0.;
    if (m_vThreads.empty())
        SetupThreads();

    for (auto& T : m_vThreads)
        T->start();
}

void gui::UpdateComputeResult()
{
    ui.edtSum->setText(QString::asprintf("%.1f", m_fSecondContainerSum));
}

void gui::SetupComputeInterval(CurvesData::iterator& begin, CurvesData::iterator& end, int thread_num)
{
    float threads_count = (float)m_vThreads.size();
    begin = m_vSecondContainer.begin() + (int)floor(float(m_vSecondContainer.size() * thread_num) / threads_count);
    end = m_vSecondContainer.begin() + (int)floor(float(m_vSecondContainer.size() * ++thread_num) / threads_count);
}

void gui::AddSecondContainerSum(double val)
{
    m_fSecondContainerSum += val;
}
