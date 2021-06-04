#include "listmachine.h"

machinelist::machinelist()
{

}

machinelist::machinelist(QVariantMap json_map)
{
    const auto count = json_map.size();
    list.resize(count+1);
    for (int i = 1; i <= count; i++){
        QVariantMap currentMap = json_map[QString::number(i)].toMap();
        QString name = currentMap["Name"].toString();
        QString description = currentMap["Description"].toString();
        QString size = currentMap["Size"].toString();
        QString machine_class = currentMap["Class"].toString();
        QString origin = currentMap["Origin"].toString();
        QString override = currentMap["Override"].toString();
        QString weakness = currentMap["Weakness"].toString();
        QString strenght = currentMap["Strenght"].toString();
        QString explosive = currentMap["Explosive_Components"].toString();
        QString picture = currentMap["Picture"].toString();
        machine mainwindow(name, description, size,
                           machine_class, origin, override,
                           weakness, strenght, explosive, picture);
        page = i;
        list[page] = mainwindow;
    }
}

machinelist::machinelist(const machinelist &base)
{
    list = base.list;
}

std::vector <machine> machinelist::getList()
{
    return list;
}
