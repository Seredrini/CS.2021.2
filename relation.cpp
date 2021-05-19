#include "relation.h"

relation::relation()
{

}

relation::relation(const relation &r)
{
    firstType = r.firstType;
    secondType = r.secondType;
    relType = r.relType;
    relID = r.relID;
}

relation::relation(monsterType *f, monsterType *s, QString t, int id)
{
    firstType =f;
    secondType = s;
    relType = t;
    relID = id;
}

monsterType* relation::getFirstType()
{
    return firstType;
}

monsterType* relation::getSecondType()
{
    return secondType;
}

QString relation::getRelType()
{
    return relType;
}

int relation::getRelID()
{
    return relID;
}

void relation::setRelID(int id)
{
    relID=id;
}

void relation::setFirstType(monsterType *f)
{
    firstType = f;
}

void relation::setSecondType(monsterType *s)
{
    secondType = s;
}

void relation::setRelType(QString t)
{
    relType = t;
}

void relation::setRelAll(monsterType *f, monsterType *s, QString t,int id)
{
    firstType =f;
    secondType = s;
    relType = t;
    relID=id;
}
