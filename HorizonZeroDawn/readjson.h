#ifndef READJSON_H
#define READJSON_H
#include <QFile>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>

class readJson
{
public:
    readJson(QString linker);
    QVariantMap getMap();
    QTextStream file_text();
    QString file;
private:
    QJsonParseError docError;
    QVariantMap json_map;
};

#endif // READJSON_H
