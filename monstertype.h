#ifndef MONSTERTYPE_H
#define MONSTERTYPE_H

#include <iostream>
#include <qstring.h>

#include "sighting.h"
#include "relation.h"


class monsterType
{
public:
    monsterType();
    monsterType(const monsterType &t);
    monsterType(QString n, int dL, monsterType *par, QString d, QVector<relation> *rel, QVector<sighting> *s);
    QString getName();
    int getDangerLevel();
    monsterType* getParentType();
    QString getDesc();
    QVector<relation>* getRelations();
    QVector<sighting>* getSightings();
    void setName(QString n);
    void setDangerLevel(int dl);
    void setParentType(monsterType *par);
    void setDesc(QString d);
    void setRelations(QVector<relation>*rel);
    void setSightings(QVector<sighting> *s);
    void setAll(QString n, int dL, monsterType *par, QString d, QVector<relation> *rel, QVector<sighting> *s);

protected:
    QString name;
    int dangerLevel;
    monsterType *parentType;
    QString desc;
    QVector<relation> *relations;
    QVector<sighting> *sightings;
};

#endif // MONSTERTYPE_H
