#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "machine.h"
#include "listmachine.h"
#include "readjson.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bkgnd(":/pics/BG.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    QString linker = ":/json/kurs.json";
    readJson read(linker);
    machinelist newList(read.getMap());
    list = newList.getList();
    machine(1);

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::machine(int page)
{
    /*QString name = (list[page].name()).join("<br>");
    QString description = (list[page].description()).join("<br>");
    QString size = (list[page].size()).join("<br>");
    QString machine_class = (list[page].machine_class()).join("<br>");
    QString origin = (list[page].origin()).join("<br>");
    QString override = (list[page].override()).join("<br>");
    QString weakness = (list[page].weakness()).join("<br>");
    QString strenght = (list[page].strenght()).join("<br>");
    QString explosive = (list[page].explosive()).join("<br>");
    QString picture = (list[page].picture()).join("<br>");*/

    ui->Name->setText(list[page].name());
    ui->Description->setText(list[page].description());
    ui->Size->setText(list[page].size());
    ui->Machine_Class->setText(list[page].machine_class());
    ui->Origin->setText(list[page].origin());
    ui->Override->setText(list[page].override());
    ui->Weakness->setText(list[page].weakness());
    ui->Strenght->setText(list[page].strenght());
    ui->Explosive->setText(list[page].explosive());
    QPixmap pix(list[page].picture());
    int w = ui->Picture->width();
    int h = ui->Picture->height();
    ui->Picture->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->Picture->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_Watcher_clicked()
{
    machine(1);
}

void MainWindow::on_Striber_clicked()
{
    machine(2);
}

void MainWindow::on_Broadhead_clicked()
{
    machine(3);
}

void MainWindow::on_Tallneck_clicked()
{
    machine(4);
}

void MainWindow::on_Charger_clicked()
{
    machine(5);
}

void MainWindow::on_Scrapper_clicked()
{
    machine(6);
}

void MainWindow::on_Grazer_clicked()
{
    machine(7);
}

void MainWindow::on_Sawtooth_clicked()
{
    machine(8);
}

void MainWindow::on_Lancehorn_clicked()
{
    machine(9);
}

void MainWindow::on_BellowbackFreeze_clicked()
{
    machine(10);
}

void MainWindow::on_BellowbackFire_clicked()
{
    machine(11);
}

void MainWindow::on_Glinthawk_clicked()
{
    machine(12);
}

void MainWindow::on_Stalker_clicked()
{
    machine(13);
}

void MainWindow::on_Trampler_clicked()
{
    machine(14);
}

void MainWindow::on_Longleg_clicked()
{
    machine(15);
}

void MainWindow::on_Ravager_clicked()
{
    machine(16);
}

void MainWindow::on_Snapmaw_clicked()
{
    machine(17);
}

void MainWindow::on_ShellWalker_clicked()
{
    machine(18);
}

void MainWindow::on_Thunderjaw_clicked()
{
    machine(19);
}

void MainWindow::on_Rockbreaker_clicked()
{
    machine(20);
}

void MainWindow::on_Stormbird_clicked()
{
    machine(21);
}

void MainWindow::on_Corruptor_clicked()
{
    machine(22);
}

void MainWindow::on_Deathbringer_clicked()
{
    machine(23);
}
