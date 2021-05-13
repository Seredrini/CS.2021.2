#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <model.h>
#include "QCompleter"
#include "QListWidgetItem"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateWords();
    void updateCurrentWord();
    void displayError(QString error);

private slots:
    void on_lineEdit_editingFinished();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_Syn_itemClicked(QListWidgetItem *item);
    void on_listWidget_Ant_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Model* model;
    QCompleter* completer;
    bool showHistory;
    bool showAddInfo;
    void selectWord(QString word);
    void setHistoryVisible(bool visible);
    void setAddInfoVisible(bool visible);
};
#endif // MAINWINDOW_H
