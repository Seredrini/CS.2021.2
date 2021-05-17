#include "treemodel.h"
#include "treeitem.h"

#include <QDebug>
#include <QtWidgets>

TreeModel::TreeModel(const QStringList &headers, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    for (const QString &header : headers)
        rootData << header;

    rootItem = new TreeItem(rootData);
    readJson();
    setupModelData(rootItem);
    writeJson();

}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *item = getItem(index);

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
//    if(index.column()==1)
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
//    else return Qt::NoItemFlags;
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return QModelIndex();

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
    const bool success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeModel::addType(QModelIndex index,QString name)
{
    monsterType m = monsterType();
    m.setName(name);
    for (int i = 0 ;i<types.size();i++){
        if (types[i].getName()==name) return true;
    }
    types.push_back(m);
    QJsonObject textObject;
    textObject["Name"] = m.getName();
    textObject["Danger level"]=0;
    textObject["Parent type"]="None";
    textObject["Description"]="Enter data";
    JTypes.append(textObject);
    writeJson();
    insertRows(index.row()+1,1);
    TreeItem *currType = rootItem->child(index.row()+1);
    currType->setData(0,m.getName());
    currType->insertChildren(0,4,rootItem->columnCount());
    currType->child(0)->setData(0,"Danger Level :");
    currType->child(0)->setData(1,"Enter data");
    currType->child(1)->setData(0,"Parent type :");
    currType->child(1)->setData(1,"None");
    currType->child(2)->setData(0,"Sightings :");
    currType->child(3)->setData(0,"Relations :");

    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    return false;
}

bool TreeModel::addSubtype(QModelIndex index, QString name)
{
    for (int i = 0 ;i<types.size();i++){
        if (types[i].getName()==name) return true;
    }
    monsterType m = monsterType();
    m.setName(name);
    QModelIndex ind =index;
    while(ind.parent().isValid()){
        ind = ind.parent();
    }
    m.setParentType(findByName(ind.data().toString()));
    types.push_back(m);
    QJsonObject textObject;
    textObject["Name"] = m.getName();
    textObject["Danger level"]=0;
    textObject["Parent type"]=ind.data().toString();
    textObject["Description"]="Enter data";
    JTypes.append(textObject);
    writeJson();
    insertRows(index.row()+1,1);
    TreeItem *currType = rootItem->child(index.row()+1);
    currType->setData(0,m.getName());
    currType->insertChildren(0,4,rootItem->columnCount());
    currType->child(0)->setData(0,"Danger Level :");
    currType->child(0)->setData(1,0);
    currType->child(1)->setData(0,"Parent type :");
    currType->child(1)->setData(1,ind.data().toString());
    currType->child(2)->setData(0,"Sightings :");
    currType->child(3)->setData(0,"Relations :");

    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    return false;
}

bool TreeModel::checkSight(QString name)
{
    for (int i = 0 ;i<allSightings.size();i++){
        if (allSightings[i].getCodename()==name) return true;
    } return false;

}

bool TreeModel::addSight(QModelIndex index, QString name,QString stat,QString desc,int amount,QString loc)
{
    sighting s = sighting(name,loc,amount,stat,desc);

    QModelIndex ind =index;
    while(ind.parent().isValid()){
        ind = ind.parent();
    }
    index = ind.child(3,0);
    QString typeName = ind.data().toString();
    QVector<sighting> currS = *findByName(typeName)->getSightings();
    currS.append(s);
    for (int i =0;i<types.size();i++){
        if (types[i].getName()==typeName)
            types[i].setSightings(&currS);
    }
    for (int i = 0;i<types.size();i++){
        QJsonObject currObj;
        QJsonValue jsonVal;
        jsonVal = JTypes[i];
        currObj = jsonVal.toObject();
        if (typeName==currObj["Name"].toString()){
            QJsonArray jSights;
            jSights = currObj["Sightings"].toArray();
            QJsonObject textObject;
            textObject["Codename"] = s.getCodename();
            jSights.append(textObject);
            currObj["Sightings"] = jSights;
            JTypes[i]=currObj;
        }
    }

    QJsonObject textObject;
    textObject["Codename"] = s.getCodename();
    textObject["Location"]=loc;
    textObject["Description"]=desc;
    textObject["Status"]=stat;
    textObject["Amount"]=amount;
    JSightings.append(textObject);
    writeJson();
}

void TreeModel::deleteType(QModelIndex i)
{
    QModelIndex ind =i;
    while(ind.parent().isValid()){
        ind = ind.parent();
    }
    QString name = getItem(ind)->data(0).toString();

    removeRows(ind.row(), 1, ind.parent());
    //Working with JSON
    for (int j = 0 ;j<types.size();j++){
        if (types[j].getName()==name){
            for(int k = 0;k<types[j].getRelations()->size();k++){
                relation rel = types[j].getRelations()->at(k);
                for (int i = 0;i<types.size();i++){
                    QJsonObject currObj;
                    QJsonValue jsonVal;
                    jsonVal = JTypes[i];
                    currObj = jsonVal.toObject();
                    QJsonArray jRels;
                    jRels = currObj["Relations"].toArray();
                    for(int i = 0; i< jRels.size();i++){
                        QJsonObject relObj;
                        QJsonValue relVal;
                        relVal= jRels[i];
                        relObj = relVal.toObject();
                        if (rel.getRelID()==relObj["ID"].toInt()){
                            jRels.removeAt(i);
                        }
                    }
                    currObj["Relations"] = jRels;
                    JTypes[i]=currObj;
                }

                for (int c = 0;c<allRelations.size();c++){
                    if((rel.getRelID()==allRelations[c].getRelID())){
                        allRelations.remove(c);
                        JRelations.removeAt(c);
                    }
                }
            }

            for (auto sights: *types[j].getSightings()){
                for (int c = 0;c<allSightings.size();c++){
                    if((sights.getCodename()==allSightings[c].getCodename())){
                        allSightings.remove(c);

                    }
                }
            }

            types.remove(j);
            JTypes.removeAt(j);
        }
    }
    writeJson();
}

bool TreeModel::deleteSight(QModelIndex index)
{
    QModelIndex ind =index;
    while(ind.parent().isValid()){
        ind = ind.parent();
    }
    QString typeName =ind.data().toString();
    if(!((index.parent().data()=="Sightings :")||(index.parent().parent().data()=="Sightings :"))){
        return true;
    } else if (index.parent().parent().data()=="Sightings :"){
        index = index.parent();
    }

    QString sightName =index.siblingAtColumn(1).data().toString();
    for (int i = 0; i<allSightings.size();i++){
        if(allSightings[i].getCodename()==sightName)
            allSightings.removeAt(i);
    }
    for (int i = 0;i<types.size();i++){
        QVector<sighting> s = *types[i].getSightings();
        for (int j = 0;j<s.size();j++){
            if (s[j].getCodename()==sightName){
                s.remove(j);
            }
        }
        types[i].setSightings(&s);
    }

    removeRows(index.row(),1,index.parent());
    for (int i = 0;i<JSightings.size();i++){
        QJsonValue jsonVal = JSightings[i];
        QJsonObject currObj = jsonVal.toObject();
        if(currObj["Codename"]==sightName)
            JSightings.removeAt(i);
    }
    for (int i = 0;i<types.size();i++){
        QJsonValue jsonVal = JTypes[i];
        QJsonObject currObj = jsonVal.toObject();
        QJsonArray jSights = currObj["Sightings"].toArray();
        for(int j = 0; j< jSights.size();j++){
            QJsonValue relVal= jSights[j];
            QJsonObject relObj = relVal.toObject();
            if (relObj["Codename"]==sightName){
                jSights.removeAt(j);

            }
        }
        currObj["Sightings"] = jSights;
        JTypes[i]=currObj;
    }

    writeJson();
    return false;
}

QString TreeModel::showCodename(QString codename)
{
    for (auto t:types){
        for (auto s:*t.getSightings()){
            if (s.getCodename()==codename){
                return t.getName();
            }
        }
    }
    return "";
}

void TreeModel::deleteRelation(QModelIndex index)
{
    QModelIndex indType =index;
    while(indType.parent().isValid()){
        indType = indType.parent();
    }
    int id=-1;
    //Working with model
    for (int i = 0; i<allRelations.size();i++){
        if((index.column()==0)&&
          ((allRelations[i].getFirstType()->getName()==index.data().toString())&&(allRelations[i].getSecondType()->getName()==indType.data())
          ||(allRelations[i].getSecondType()->getName()==index.data().toString())&&(allRelations[i].getFirstType()->getName()==indType.data()))
           &&(allRelations[i].getRelType()==index.siblingAtColumn(1).data())){
            id =allRelations[i].getRelID();
            allRelations.remove(i);
        }else
            if((index.column()==1)&&
                ((allRelations[i].getFirstType()->getName()==index.siblingAtColumn(0).data().toString())&&(allRelations[i].getSecondType()->getName()==indType.data())
                ||(allRelations[i].getSecondType()->getName()==index.siblingAtColumn(0).data().toString())&&(allRelations[i].getFirstType()->getName()==indType.data()))
                &&(allRelations[i].getRelType()==index.data())){
            id =allRelations[i].getRelID();
            allRelations.remove(i);
        }
    }
    for (int i = 0;i<types.size();i++){
        QVector<relation> s = *types[i].getRelations();
        for (int j = 0;j<s.size();j++){
            if (s[j].getRelID()==id){
                s.remove(j);
            }
        }
        types[i].setRelations(&s);
    }
    for (int i =0;i<JTypes.size();i++){
        QJsonObject currObj;
        QJsonValue jsonVal;
        jsonVal = JTypes[i];
        currObj = jsonVal.toObject();
        QJsonArray jRels;
        jRels = currObj["Relations"].toArray();
        for(int j = 0; j< jRels.size();j++){
            QJsonObject relObj;
            QJsonValue relVal;
            relVal= jRels[j];
            relObj = relVal.toObject();
            bool res = id==relObj["ID"].toInt();
            if (id==relObj["ID"].toInt()){
                jRels.removeAt(j);
            }
        }
        currObj["Relations"] = jRels;
        JTypes[i]=currObj;
    }
    for (int i =0;i<JRelations.size();i++){
        QJsonValue jsonVal = JRelations[i];
        QJsonObject currObj = jsonVal.toObject();
        if(currObj["Relation ID"]==id)
            JRelations.removeAt(i);
    }
    writeJson();
}

bool TreeModel::addRel(QModelIndex index, QString t, QString s)
{
    QModelIndex ind =index;
    while(ind.parent().isValid()){
        ind = ind.parent();
    }
    relation r = relation(findByName(ind.data().toString()),findByName(s),t,currRelID+1);
    if (r.getSecondType()->getDesc()=="smth wrong")
        return true;
    for (auto rel: allRelations){
        if (((rel.getFirstType()->getName()==ind.data().toString())&&(rel.getSecondType()->getName()==s))||((rel.getSecondType()->getName()==ind.data().toString())&&(rel.getFirstType()->getName()==s)))
            return true;
    }
    allRelations.push_back(r);
    for (int i = 0; i<types.size();i++){
        if (types[i].getName()==ind.data().toString()){
            QVector<relation> currRel =*types[i].getRelations();
            currRel.push_back(r);
            types[i].setRelations(&currRel);
        }
    }
    for (int i = 0;i<types.size();i++){
        QJsonObject currObj;
        QJsonValue jsonVal;
        jsonVal = JTypes[i];
        currObj = jsonVal.toObject();
        if (s==currObj["Name"].toString()){
            QJsonArray jRels;
            jRels = currObj["Relations"].toArray();
            QJsonObject textObject;
            textObject["ID"] = currRelID+1;
            jRels.append(textObject);
            currObj["Relations"] = jRels;
            JTypes[i]=currObj;
        }
    }
    for (int i = 0;i<types.size();i++){
        QJsonObject currObj;
        QJsonValue jsonVal;
        jsonVal = JTypes[i];
        currObj = jsonVal.toObject();
        if (ind.data().toString()==currObj["Name"].toString()){
            QJsonArray jRels;
            jRels = currObj["Relations"].toArray();
            QJsonObject textObject;
            textObject["ID"] = currRelID+1;
            jRels.append(textObject);
            currObj["Relations"] = jRels;
            JTypes[i]=currObj;
        }
    }
    QJsonObject textObject;
    textObject["Relation ID"]=currRelID+1;
    textObject["First type"]=ind.data().toString();
    textObject["Second type"]=s;
    textObject["Relation Type"]=t;
    JRelations.append(textObject);
    currRelID++;
    writeJson();
    return false;
}

QString TreeModel::showSubtype(QModelIndex index)
{
    QModelIndex ind =index;
    while(ind.parent().isValid()){
        ind = ind.parent();
    }
    QString names;
    for (auto i:types){
        if (i.getParentType()->getName()==ind.data().toString())
            names=names+i.getName()+" , ";
    }
    names.remove(names.length()-3,3);
    return names;
}


bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = parentItem->insertChildren(position,
                                                    rows,
                                                    rootItem->columnCount());
    endInsertRows();

    return success;
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem ? childItem->parent() : nullptr;

    if (parentItem == rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    beginRemoveColumns(parent, position, position + columns - 1);
    const bool success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

void TreeModel::writeJson()
{
    QFile* out = f;
    if (!out->open(QIODevice::WriteOnly))
        {
            return;
        }
    QJsonObject root;
    root["Types"] = JTypes;
    root["Sightings"] = JSightings;
    root["Relations"] = JRelations;
    out->write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    out->close();
}

void TreeModel::readJson()
{
    if (!f->open(QFile::ReadOnly)){
                return;
        }
    savedData = f->readAll();
    f->close();
    QJsonDocument jsonDocument(QJsonDocument::fromJson(savedData));
    QJsonObject obj  = jsonDocument.object();
    JTypes = obj["Types"].toArray();
    JRelations = obj["Relations"].toArray();
    JSightings = obj["Sightings"].toArray();
    for(int i = 0; i < JTypes.size(); i++){
        monsterType m = monsterType();
        QJsonObject currObj;
        QJsonValue jsonVal;
        jsonVal = JTypes[i];
        currObj = jsonVal.toObject();
        m.setName(currObj["Name"].toString());
        m.setDesc(currObj["Description"].toString());
        m.setDangerLevel(currObj["Danger level"].toInt());
        types.push_back(m);
    }
    for(int i = 0; i < JSightings.size(); i++){
        sighting s = sighting();
        QJsonObject currObj;
        QJsonValue jsonVal;
        jsonVal= JSightings[i];
        currObj = jsonVal.toObject();
        s.setCodename(currObj["Codename"].toString());
        s.setAmount(currObj["Amount"].toInt());
        s.setLocation(currObj["Location"].toString());
        s.setStatus(currObj["Status"].toString());
        s.setSightDesc(currObj["Description"].toString());
        allSightings.push_back(s);
    }
    for(int i = 0; i < JRelations.size(); i++){
        relation r = relation();
        QJsonObject currObj;
        QJsonValue jsonVal;
        jsonVal= JRelations[i];
        currObj = jsonVal.toObject();
        if(currRelID<=currObj["Relation ID"].toInt())
            currRelID=currObj["Relation ID"].toInt()+1;
        r.setRelID(currObj["Relation ID"].toInt());
        r.setRelType(currObj["Relation Type"].toString());
        r.setFirstType(findByName(currObj["First type"].toString()));
        r.setSecondType(findByName(currObj["Second type"].toString()));
        allRelations.push_back(r);
    }
    for(int i = 0; i < JTypes.size(); i++){
        QVector<relation> *currRel = new QVector<relation>;
        QVector<sighting> *currSight = new QVector<sighting>;
        QJsonObject currObj;
        QJsonValue jsonVal;
        jsonVal = JTypes[i];
        currObj = jsonVal.toObject();
        types[i].setParentType(findByName(currObj["Parent type"].toString()));
        QJsonArray jRels;
        QJsonArray jSights;
        jRels = currObj["Relations"].toArray();
        jSights = currObj["Sightings"].toArray();
        for(int i = 0; i< jRels.size();i++){
            QJsonObject relObj;
            QJsonValue relVal;
            relVal= jRels[i];
            relObj = relVal.toObject();
            currRel->push_back(*findByID(relObj["ID"].toInt()));
        }
        for(int i = 0; i< jSights.size();i++){
            QJsonObject sightObj;
            QJsonValue sightVal;
            sightVal= jSights[i];
            sightObj = sightVal.toObject();
            currSight->push_back(*findByCodename(sightObj["Codename"].toString()));
        }
        types[i].setRelations(currRel);
        types[i].setSightings(currSight);
    }
    QFile* out = new QFile("E:/backup.json");
    if (!out->open(QIODevice::WriteOnly))
        {
            return;
        }
    QJsonObject root;
    root["Types"] = JTypes;
    root["Relations"] = JRelations;
    out->write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    out->close();
}



bool TreeModel::search(QString name)
{
    bool check = false;
    int number =-1;
    for (int i =0;i<rootItem->childCount();i++){
        if(rootItem->child(i)->data(0)==name){
            check= true;
            number = i;
            break;
        }
    }
    if (check){
        TreeItem* needed= rootItem->child(number);
        removeRows(number+1,rootItem->childCount()-number-1);
        removeRows(0,number);
        return false;
    } else
        return true;
}


int TreeModel::rowCount(const QModelIndex &parent) const
{
    const TreeItem *parentItem = getItem(parent);

    return parentItem ? parentItem->childCount() : 0;
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;
    TreeItem *item = getItem(index);
    if (index.column()==0) return true;
    QModelIndex typeIndex = index;
    while(typeIndex.parent().isValid()){
        typeIndex = typeIndex.parent();
    }
    //Description
    if (index.parent().isValid()==false){
        for (int i = 0;i<types.size();i++){
            if(types[i].getName()==index.siblingAtColumn(0).data().toString()){
                types[i].setDesc(value.toString());
            }
        }
        for (int i =0;i<JTypes.size();i++){
            QJsonObject currObj =JTypes[i].toObject();
            if (currObj["Name"]==index.siblingAtColumn(0).data().toString()){
                currObj["Description"]=value.toString();
            }
            JTypes[i]=currObj;
        }
    }
    //Danger level
    if (index.siblingAtColumn(0).data().toString()=="Danger Level :"){
        if(strcmp(value.typeName(),"int") == 0){
            for (int i = 0;i<types.size();i++){
                if(types[i].getName()==index.parent().siblingAtColumn(0).data().toString()){
                    types[i].setDangerLevel(value.toInt());
                }
            }
            for (int i =0;i<JTypes.size();i++){
                QJsonObject currObj =JTypes[i].toObject();
                if (currObj["Name"]==index.parent().siblingAtColumn(0).data().toString()){
                    currObj["Danger level"]=value.toInt();
                }
                JTypes[i]=currObj;
            }
        }
    }
    // Sightings status
    if (index.siblingAtColumn(0).data().toString()=="Status"){
        for (int i = 0;i<types.size();i++){
            if(types[i].getName()==typeIndex.data().toString()){
                QVector<sighting> sights =*types[i].getSightings();
                for (int j= 0;j<sights.size();j++){
                    if(sights[j].getCodename()==index.parent().siblingAtColumn(1).data().toString()){
                        sights[j].setStatus(value.toString());
                    }
                }
            }
        }
        for (int i = 0;i<allSightings.size();i++){
            if (allSightings[i].getCodename()==index.parent().siblingAtColumn(1).data().toString()){
                allSightings[i].setStatus(value.toString());
            }
        }
        for (int i = 0; i<JSightings.size();i++){
            QJsonObject currObj =JSightings[i].toObject();
            if (currObj["Codename"].toString()==index.parent().siblingAtColumn(1).data().toString()){
                currObj["Status"] = value.toString();
            }
            JSightings[i] = currObj;
        }
    }
    // Sightings amount
    if (index.siblingAtColumn(0).data().toString()=="Amount"){
        if(strcmp(value.typeName(),"int") == 0){
            for (int i = 0;i<types.size();i++){
                if(types[i].getName()==typeIndex.data().toString()){
                    QVector<sighting> sights =*types[i].getSightings();
                    for (int j= 0;j<sights.size();j++){
                        if(sights[j].getCodename()==index.parent().siblingAtColumn(1).data().toString()){
                            sights[j].setAmount(value.toInt());
                        }
                    }
                }
            }
            for (int i = 0;i<allSightings.size();i++){
                if (allSightings[i].getCodename()==index.parent().siblingAtColumn(1).data().toString()){
                    allSightings[i].setAmount(value.toInt());
                }
            }
            for (int i = 0; i<JSightings.size();i++){
                QJsonObject currObj =JSightings[i].toObject();
                if (currObj["Codename"].toString()==index.parent().siblingAtColumn(1).data().toString()){
                    currObj["Amount"] = value.toInt();
                }
                JSightings[i] = currObj;
            }
        }
    }
    //Sightings description
    if (index.siblingAtColumn(0).data().toString()=="Description"){
        for (int i = 0;i<types.size();i++){
            if(types[i].getName()==typeIndex.data().toString()){
                QVector<sighting> sights =*types[i].getSightings();
                for (int j= 0;j<sights.size();j++){
                    if(sights[j].getCodename()==index.parent().siblingAtColumn(1).data().toString()){
                        sights[j].setSightDesc(value.toString());
                    }
                }
            }
        }
        for (int i = 0;i<allSightings.size();i++){
            if (allSightings[i].getCodename()==index.parent().siblingAtColumn(1).data().toString()){
                allSightings[i].setSightDesc(value.toString());
            }
        }
        for (int i = 0; i<JSightings.size();i++){
            QJsonObject currObj =JSightings[i].toObject();
            if (currObj["Codename"].toString()==index.parent().siblingAtColumn(1).data().toString()){
                currObj["Description"] = value.toString();
            }
            JSightings[i] = currObj;
        }
    }
    //Sightings location
    if (index.siblingAtColumn(0).data().toString()=="Location"){
        for (int i = 0;i<types.size();i++){
            if(types[i].getName()==typeIndex.data().toString()){
                QVector<sighting> sights =*types[i].getSightings();
                for (int j= 0;j<sights.size();j++){
                    if(sights[j].getCodename()==index.parent().siblingAtColumn(1).data().toString()){
                        sights[j].setLocation(value.toString());
                    }
                }
            }
        }
        for (int i = 0;i<allSightings.size();i++){
            if (allSightings[i].getCodename()==index.parent().siblingAtColumn(1).data().toString()){
                allSightings[i].setLocation(value.toString());
            }
        }
        for (int i = 0; i<JSightings.size();i++){
            QJsonObject currObj =JSightings[i].toObject();
            if (currObj["Codename"].toString()==index.parent().siblingAtColumn(1).data().toString()){
                currObj["Location"] = value.toString();
            }
            JSightings[i] = currObj;
        }
    }
    writeJson();
    bool result = item->setData(index.column(), value);
    if (result)
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void TreeModel::setupModelData(TreeItem *root)
{
    QVector<TreeItem*> parents;
    parents << root;
    for (int i = 0; i<types.size();i++){
        root->insertChildren(i,1,root->columnCount());
        root->child(i)->setData(0,types[i].getName());
        root->child(i)->setData(1,types[i].getDesc());
        root->child(i)->insertChildren(0,4,root->columnCount());
        root->child(i)->child(0)->setData(0,"Danger Level :");
        root->child(i)->child(0)->setData(1,types[i].getDangerLevel());
        root->child(i)->child(1)->setData(0,"Parent type :");
        root->child(i)->child(1)->setData(1,types[i].getParentType()->getName());
        root->child(i)->child(2)->setData(0,"Sightings :");

        TreeItem* parentSight = root->child(i)->child(2);
        parentSight->insertChildren(0,types[i].getSightings()->size(),root->columnCount());
        for(int j = 0; j <types[i].getSightings()->size();j++){
            QVector<sighting> s = *types[i].getSightings();
            parentSight->child(j)->setData(0,"Codename");
            parentSight->child(j)->setData(1,s[j].getCodename());
            parentSight->child(j)->insertChildren(0,4,root->columnCount());
            TreeItem* sightPars =  parentSight->child(j);
            sightPars->child(0)->setData(0,"Status");
            sightPars->child(0)->setData(1,s[j].getStatus());
            sightPars->child(1)->setData(0,"Amount");
            sightPars->child(1)->setData(1,s[j].getAmount());
            sightPars->child(2)->setData(0,"Description");
            sightPars->child(2)->setData(1,s[j].getSightDesc());
            sightPars->child(3)->setData(0,"Location");
            sightPars->child(3)->setData(1,s[j].getLocation());
        }

        TreeItem* parentRel = root->child(i)->child(3);
        parentRel->setData(0,"Relations :");
        parentRel->insertChildren(0,types[i].getRelations()->size(),root->columnCount());
        for(int j = 0; j <types[i].getRelations()->size();j++){
            QVector<relation> r = *types[i].getRelations();
            if (types[i].getName()==r[j].getFirstType()->getName())
                parentRel->child(j)->setData(0,r[j].getSecondType()->getName());
            else if (types[i].getName()==r[j].getSecondType()->getName())
                parentRel->child(j)->setData(0,r[j].getFirstType()->getName());
            parentRel->child(j)->setData(1,r[j].getRelType());
        }
    }
}

monsterType *TreeModel::findByName(QString n)
{
    for (int i =0;i<types.size();i++){
        if (types[i].getName()==n) return &types[i];
    }
    QVector<relation> *rel = new QVector<relation>;
    QVector<sighting> *s = new QVector<sighting>;
    monsterType *m =new monsterType("None",0,nullptr,"smth wrong", rel, s);
    return m;
}

sighting *TreeModel::findByCodename(QString c)
{
    for (int i =0;i<allSightings.size();i++){
        if (allSightings[i].getCodename()==c){

            return &allSightings[i];
        }
    }
    sighting *s = new sighting("Error c",    "Error loc",    0,    "Error st",    "Error");
    qDebug()<<"Find by code error";
    return s;
}

relation *TreeModel::findByID(int id)
{
    for (int i =0;i<allRelations.size();i++){
        if (allRelations[i].getRelID()==id) {
            return &allRelations[i];
        }
    }
    QVector<relation> *rel = new QVector<relation>;
    QVector<sighting> *s = new QVector<sighting>;
    monsterType *m1 =new monsterType("error1",0,nullptr,"smth wrong", rel, s);
    monsterType *m2 =new monsterType("error2",0,nullptr,"smth wrong", rel, s);
    relation *r = new relation(m1, m2, "Error t",0);
    qDebug()<<"Find by id error";
    return r;
}

