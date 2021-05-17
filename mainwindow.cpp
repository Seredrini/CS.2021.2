#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "errmsg.h"
#include "sightinput.h"

#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
         headers<<"Title"<<"Description";
//#283873 #8e86ff #1c376a #162B53
        model = new TreeModel(headers);
        ui->treeView->setStyleSheet("QScrollBar:vertical {background:#1c376a }  QHeaderView::section { background-color:#1c376a;color:white} QTreeView {background-color:black;color:#0092cc } QTreeView::item:selected{background-color:#282828}"
"QTreeView::item:selected:!active {color:white}");
        ui->treeView->setModel(model);
        ui->treeView->setColumnWidth(0,200);

}

void MainWindow::showError(QString name)
{
    errMsg *null = new errMsg;
    QObject::connect(this, SIGNAL(sendText(QString)), null, SLOT(getText(QString)));
    emit sendText(name);
    null->setWindowIcon(QIcon(":/icon/error.ico"));
    null->show();
}


void MainWindow::getDataSight(QString name, QString stat, QString desc, int amount, QString loc)
{
    model->addSight(ui->treeView->selectionModel()->currentIndex(), name, stat, desc, amount, loc);
}

void MainWindow::on_addType_clicked()
{

    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QString name = ui->nameEdit->text();
    if (name == ""){
           showError("No data entered");
    } else
    if(model->addType(index,name)){
        showError("The type with this name already exists");
    }
    ui->nameEdit->clear();
}

void MainWindow::on_delType_clicked()
{
    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    model->deleteType(index);
}

void MainWindow::on_addSight_clicked()
{
    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QString name = ui->nameSight->text();
    if (name == ""){
           showError("No data entered");
    } else
    if(model->checkSight(name)){
        showError("The sighing with this codename already exists");
    }else{
        sightInput *s = new sightInput;
        QObject::connect(this, SIGNAL(sendText(QString)), s, SLOT(getText(QString)));
        QObject::connect(s, SIGNAL(sendData(QString,QString,QString,int,QString )), this, SLOT(getDataSight(QString,QString,QString,int,QString)));
        emit sendText(name);
        s->setWindowIcon(QIcon(":/icon/grimoire.ico"));
        s->setWindowTitle("Enter data");
        s->show();
    }
    ui->nameSight->clear();
}

void MainWindow::on_deleteSight_clicked()
{
    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    if(model->deleteSight(index)){
        errMsg *name = new errMsg;
        QObject::connect(this, SIGNAL(sendText(QString)), name, SLOT(getText(QString)));
        emit sendText("Please select a sighting");
        name->setWindowIcon(QIcon(":/icon/error.ico"));
        name->show();
    }
}

void MainWindow::on_addRelation_clicked()
{
    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QString type = ui->relType->text();
    QString sec = ui->relSecType->text();
    if(model->addRel(index,type,sec)){
        showError("Please enter all the neccessary data");
    }
    ui->relSecType->clear();
    ui->relType->clear();
}

void MainWindow::on_deleteRelation_clicked()
{
    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    if (index.parent().data()!="Relations :"){
        showError("Please select a relation");
       }
    else{
        model->deleteRelation(index);
    }
}

void MainWindow::on_apply_clicked()
{
    ui->searchName->clear();
    model = new TreeModel(headers);
    ui->apply->setText("Apply");
    ui->treeView->setModel(model);
    ui->treeView->setColumnWidth(0,200);
}

void MainWindow::on_search_clicked()
{
    if(model->search(ui->searchName->text())){
        showError("No monster with this name");
    }else{
        ui->apply->setText("Return");
        ui->treeView->expandAll();
    }

}

void MainWindow::on_addSubtype_clicked()
{
    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QString name = ui->nameEdit->text();
    if (name == ""){
           showError("No data entered");
    } else
    if(model->addSubtype(index,name)){
        showError("The type with this name already exists");
    }
    ui->nameEdit->clear();
}

void MainWindow::on_showSubtypes_clicked()
{
    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QString names = model->showSubtype(index);
    if (names==""){
        showError("No subtypes");
    } else{
        errMsg *name = new errMsg;
        QObject::connect(this, SIGNAL(sendText(QString)), name, SLOT(getText(QString)));
        emit sendText(names);
        name->setWindowTitle("Subtypes");
        name->setWindowIcon(QIcon(":/icon/grimoire.ico"));
        name->setStyleSheet("background-color:#43587f;color:white");
        name->show();
    }

}

void MainWindow::on_actionExpand_triggered()
{
    ui->treeView->expandAll();
}

void MainWindow::on_actionCollapse_triggered()
{
    ui->treeView->collapseAll();

}

void MainWindow::on_showCodename_clicked()
{
    QString typeName="";
    QString codename = ui->codename->text();
    if (codename==""){
        showError("Enter the codename");
    } else {
        typeName = model->showCodename(codename);
    }
    if (typeName==""){
        showError("No such codename");
    } else{
        model->search(typeName);
        ui->apply->setText("Return");
        ui->treeView->expandAll();
    }
    ui->codename->clear();
}
