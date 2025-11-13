
#include "MainController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainController* c = new MainController();
    return a.exec();
}
