#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/icon/grimoire.ico"));
    w.show();
    return a.exec();
}
