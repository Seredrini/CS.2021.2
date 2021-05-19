#include "sighting.h"

sighting::sighting()
{
    codename = "Unknown";
    location = "Neverland";
    status = "Unknown";
    sightDesc = "Sighting created without any data";
    amount = 0;
}

sighting::sighting(const sighting &s)
{
    codename = s.codename;
    location = s.location;
    status = s.status;
    sightDesc = s.sightDesc;
    amount = s.amount;
}

sighting::sighting(QString c, QString loc, int am, QString st, QString desc)
{
    codename = c;
    location = loc;
    status = st;
    sightDesc = desc;
    amount = am;
}

QString sighting::getCodename()
{
    return codename;
}

QString sighting::getLocation()
{
    return location;
}

QString sighting::getStatus()
{
    return status;
}

QString sighting::getSightDesc()
{
    return sightDesc;
}

int sighting::getAmount()
{
    return amount;
}

void sighting::setCodename(QString c)
{
    codename = c;
}

void sighting::setLocation(QString l)
{
    location = l;
}

void sighting::setStatus(QString s)
{
    status = s;
}

void sighting::setSightDesc(QString d)
{
    sightDesc = d;
}

void sighting::setAmount(int am)
{
    amount =am;
}

void sighting::setSightAll(QString c, QString loc, int am, QString st, QString desc)
{
    codename = c;
    location = loc;
    status = st;
    sightDesc = desc;
    amount = am;
}
