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

void gui::ComputeSecondContainer()
{
    float sum = 0.f;
    for (const auto& I : m_vSecondContainer)
        sum += I->R1();
    ui.edtSum->setText(QString::asprintf("%.1f", sum));
}
