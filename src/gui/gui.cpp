#include "gui.h"

gui::gui() : error_mb(this), model(curves)
{
    ui.setupUi(this);
    error_mb.setText("Failed to load curves.dll!");
    ui.tvObjects->setModel(&model);
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
        model.update(cnt);
    }
}
