#ifndef RELATION_H
#define RELATION_H


#include <QString>
#include <iostream>


class monsterType;

class relation
{
public:
    relation();
    relation(const relation &r);
    relation(monsterType *f, monsterType *s, QString t,int id);
    monsterType *getFirstType();
    monsterType *getSecondType();
    QString getRelType();
    int getRelID();
    void setRelID(int id);
    void setFirstType(monsterType *f);
    void setSecondType(monsterType *s);
    void setRelType(QString t);
    void setRelAll(monsterType *f, monsterType *s, QString t,int id);
protected:
    int relID;
    monsterType *firstType;
    monsterType *secondType;
    QString relType;
};

#endif // RELATION_H
