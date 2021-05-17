#include "sightinput.h"
#include "ui_sightinput.h"

sightInput::sightInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sightInput)
{
    ui->setupUi(this);
}

sightInput::~sightInput()
{
    delete ui;
}

void sightInput::getText(QString msg)
{
    ui->label->setText(msg);
}

void sightInput::on_buttonBox_accepted()
{
    emit sendData(ui->label->text(),ui->status->text(),ui->desc->text(),ui->amount->text().toInt(),ui->location->text());
}

void sightInput::on_buttonBox_rejected()
{
    close();
}

