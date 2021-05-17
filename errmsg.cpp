#include "errmsg.h"
#include "ui_errmsg.h"

errMsg::errMsg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::errMsg)
{
    ui->setupUi(this);

}

errMsg::~errMsg()
{
    delete ui;
}

void errMsg::getText(QString msg)
{
    ui->label->setText(msg);
}

