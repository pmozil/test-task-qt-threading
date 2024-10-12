#include "threadsdemowindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ThreadsDemoWindow w;

    w.show();
    return a.exec();
}
