#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QIcon>
#include <machine.h>
#include <vector>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    vector<machine> list;
    void machine(int param);

private slots:
    void on_Watcher_clicked();

    void on_Striber_clicked();

    void on_Broadhead_clicked();

    void on_Tallneck_clicked();

    void on_Charger_clicked();

    void on_Scrapper_clicked();

    void on_Grazer_clicked();

    void on_Sawtooth_clicked();

    void on_Lancehorn_clicked();

    void on_BellowbackFreeze_clicked();

    void on_BellowbackFire_clicked();

    void on_Glinthawk_clicked();

    void on_Stalker_clicked();

    void on_Trampler_clicked();

    void on_Longleg_clicked();

    void on_Ravager_clicked();

    void on_Snapmaw_clicked();

    void on_ShellWalker_clicked();

    void on_Thunderjaw_clicked();

    void on_Rockbreaker_clicked();

    void on_Stormbird_clicked();

    void on_Corruptor_clicked();

    void on_Deathbringer_clicked();

private:
    Ui::MainWindow *ui;
    int page;
    QString linker,param;

};
#endif // MAINWINDOW_H
