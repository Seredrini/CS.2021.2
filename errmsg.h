#ifndef ERRMSG_H
#define ERRMSG_H

#include <QDialog>

namespace Ui {
class errMsg;
}

class errMsg : public QDialog
{
    Q_OBJECT

public:
    explicit errMsg(QWidget *parent = nullptr);
    ~errMsg();
public slots:
    void getText (QString msg);
private:
    Ui::errMsg *ui;
};

#endif // ERRMSG_H
