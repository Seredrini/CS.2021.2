#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "treemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void showError(QString name);

private slots:

    void on_addType_clicked();

    void on_delType_clicked();

    void getDataSight(QString name,QString stat,QString desc,int amount,QString loc);

    void on_addSight_clicked();

    void on_deleteSight_clicked();

    void on_addRelation_clicked();

    void on_deleteRelation_clicked();

    void on_apply_clicked();

    void on_search_clicked();


    void on_addSubtype_clicked();

    void on_showSubtypes_clicked();

    void on_actionExpand_triggered();

    void on_actionCollapse_triggered();

    void on_showCodename_clicked();

signals:
    void sendText(QString);
private:
    Ui::MainWindow *ui;
    TreeModel *model;
    QStringList headers;
};

#endif // MAINWINDOW_H
