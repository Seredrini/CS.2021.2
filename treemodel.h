#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QModelIndex>
#include <QVariant>
#include "monstertype.h"
#include "treeitem.h"
#include "relation.h"
#include "sighting.h"

class TreeItem;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(const QStringList &headers, /*const QString &data,*/
              QObject *parent = nullptr);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override;

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    TreeItem *getItem(const QModelIndex &index) const;
    void writeJson();
    void readJson();
    bool search(QString name);
    bool addType(QModelIndex index,QString name);
    bool addSubtype(QModelIndex index,QString name);
    bool checkSight(QString name);
    bool addSight(QModelIndex index,QString name,QString stat,QString desc,int amount,QString loc);
    void deleteType(QModelIndex index);
    bool deleteSight(QModelIndex index);
    QString showCodename(QString codename);
    void deleteRelation(QModelIndex index);
    bool addRel(QModelIndex index,QString t,QString s);
    QString showSubtype(QModelIndex index);
    monsterType *findByName(QString n);
    sighting *findByCodename(QString c);
    relation *findByID(int id);

    void debug();
private:

    QFile *f = new QFile("kursData.json");



    void setupModelData(TreeItem *parent);


    TreeItem *rootItem;
    QVector<monsterType> types;
    QVector<sighting> allSightings;
    QVector<relation> allRelations;
    QJsonArray JRelations;
    QJsonArray JTypes;
    QJsonArray JSightings;
    QByteArray savedData;
    int currRelID=1000;
};

#endif // TREEMODEL_H
