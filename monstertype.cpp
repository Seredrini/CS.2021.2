#include "monstertype.h"

monsterType::monsterType()
{
    parentType=nullptr;
}

monsterType::monsterType(const monsterType &t)
{
    name = t.name;
    dangerLevel = t.dangerLevel;
    parentType = t.parentType;
    sightings = t.sightings;
    relations = t.relations;
    desc = t.desc;
}

monsterType::monsterType(QString n, int dL, monsterType *par, QString d, QVector<relation> *rel, QVector<sighting> *s)
{
    name = n;
    dangerLevel = dL;
    parentType = par;
    sightings = s;
    relations = rel;
    desc = d;
}

QString monsterType::getName()
{
    return name;
}

int monsterType::getDangerLevel()
{
    return dangerLevel;
}

monsterType *monsterType::getParentType()
{
    return parentType;
}

QString monsterType::getDesc()
{
    return desc;
}

QVector<relation>* monsterType::getRelations()
{
    return relations;
}

QVector<sighting>* monsterType::getSightings()
{
    return sightings;
}

void monsterType::setName(QString n)
{
    name = n;
}

void monsterType::setDangerLevel(int dl)
{
    dangerLevel = dl;
}

void monsterType::setParentType(monsterType *par)
{
    parentType = par;
}

void monsterType::setDesc(QString d)
{
    desc = d;
}

void monsterType::setRelations(QVector<relation> *rel)
{
    relations = rel;
}

void monsterType::setSightings(QVector<sighting> *s)
{
    sightings = s;
}

void monsterType::setAll(QString n, int dL, monsterType *par, QString d, QVector<relation> *rel, QVector<sighting> *s)
{
    name = n;
    dangerLevel = dL;
    parentType = par;
    sightings = s;
    relations = rel;
    desc = d;
}
