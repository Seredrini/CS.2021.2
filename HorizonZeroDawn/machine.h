#ifndef MACHINE_H
#define MACHINE_H

#include <QString>
#include <QList>

class machine
{
public:
    machine();

    machine(QString nameC,
            QString descriptionC,
            QString sizeC,
            QString machine_classC,
            QString originC,
            QString overrideC,
            QString weaknessC,
            QString strenghtC,
            QString explosiveC,
            QString pictureC);

    machine(const machine &v);

    ~machine();

    QString name();
    QString description();
    QString size();
    QString machine_class();
    QString origin();
    QString override();
    QString weakness();
    QString strenght();
    QString explosive();
    QString picture();

    QString nameT= "";
    QString descriptionT= "";
    QString sizeT= "";
    QString machine_classT= "";
    QString originT= "";
    QString overrideT= "";
    QString weaknessT= "";
    QString strenghtT= "";
    QString explosiveT= "";
    QString pictureT= "";
};

#endif // MACHINE_H
