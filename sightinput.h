#ifndef SIGHTINPUT_H
#define SIGHTINPUT_H

#include <QDialog>

namespace Ui {
class sightInput;
}

class sightInput : public QDialog
{
    Q_OBJECT

public:
    explicit sightInput(QWidget *parent = nullptr);
    ~sightInput();
signals:
   void sendData(QString name,QString stat,QString desc,int amount,QString loc);
public slots:
    void getText (QString msg);
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::sightInput *ui;
};

#endif // SIGHTINPUT_H
