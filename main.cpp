#include "view/mainwindow.h"
#include "controller/controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Controller controller;

   // QObject::connect(&controller, SIGNAL(returnIteration(QString)), &w, SLOT(addIteration(QString)));
    QObject::connect(&w, SIGNAL(startSimulation(Settings)), &controller, SLOT(beginSimulation(Settings)));
    w.show();
    try{
        return a.exec();
    }catch(...)
    {
        return 1;
    }

}

