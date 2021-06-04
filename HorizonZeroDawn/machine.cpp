#include "machine.h"
#include "mainwindow.h"

machine::machine()
{

}

machine::machine(QString nameC, QString descriptionC, QString sizeC,
                 QString machine_classC, QString originC, QString overrideC,
                 QString weaknessC, QString strenghtC, QString explosiveC, QString pictureC)
{
    nameT = nameC;
    descriptionT = descriptionC;
    sizeT = sizeC;
    machine_classT = machine_classC;
    originT = originC;
    overrideT = overrideC;
    weaknessT = weaknessC;
    strenghtT = strenghtC;
    explosiveT = explosiveC;
    pictureT = pictureC;
}

machine::machine(const machine &v)
{
    nameT = v.nameT;
    descriptionT = v.descriptionT;
    sizeT = v.sizeT;
    machine_classT = v.machine_classT;
    originT = v.originT;
    overrideT = v.overrideT;
    weaknessT = v.weaknessT;
    strenghtT = v.strenghtT;
    explosiveT = v.explosiveT;
    pictureT = v.pictureT;
}

machine::~machine()
{

}

QString machine::name()
{
    return nameT;
}

QString machine::description()
{
    return descriptionT;
}

QString machine::size()
{
    return sizeT;
}

QString machine::machine_class()
{
    return machine_classT;
}

QString machine::origin()
{
    return originT;
}

QString machine::override()
{
    return overrideT;
}

QString machine::weakness()
{
    return weaknessT;
}

QString machine::strenght()
{
    return strenghtT;
}

QString machine::explosive()
{
    return explosiveT;
}

QString machine::picture()
{
    return pictureT;
}


