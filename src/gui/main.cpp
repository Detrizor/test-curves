#include "gui.h"
#include <QtWidgets/QApplication>

gui* CComputeObject::m_pGui;
int main(int argc, char *argv[])
{
	std::srand(std::time(NULL));
    QApplication a(argc, argv);
    gui w;
    w.show();
    return a.exec();
}
