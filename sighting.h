#ifndef SIGHTING_H
#define SIGHTING_H

#include <QString>


class sighting
{
public:
    sighting();
    sighting(const sighting &s);
    sighting(QString c,    QString loc,    int am,    QString st,    QString desc);
    QString getCodename();
    QString getLocation();
    QString getStatus();
    QString getSightDesc();
    int getAmount();
    void setCodename(QString c);
    void setLocation(QString l);
    void setStatus(QString s);
    void setSightDesc(QString d);
    void setAmount(int am);
    void setSightAll(QString c,    QString loc,    int am,    QString st,    QString desc);
protected:
    QString codename;
    QString location;
    int amount;
    QString status;
    QString sightDesc;
};

#endif // SIGHTING_H
