#include "gui.h"

gui::gui() : error_mb(this), model(curves)
{
    ui.setupUi(this);
    error_mb.setText("Failed to load curves.dll!");
    ui.tvObjects->setModel(&model);
    ui.tvObjects->setColumnWidth(0, 50);
    ui.tvObjects->setColumnWidth(1, 100);
    ui.tvObjects->setColumnWidth(2, 100);
    ui.tvObjects->setColumnWidth(3, 300);
    ui.tvObjects->setColumnWidth(4, 300);
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
