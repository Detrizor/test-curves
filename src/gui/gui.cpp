#include "gui.h"

gui::gui(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    pApi = std::make_unique<CAPI>();
}
