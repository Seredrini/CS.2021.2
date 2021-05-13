#ifndef NETWORKACCESS_H
#define NETWORKACCESS_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include "word.h"

class NetworkAccess : public QObject
{
    Q_OBJECT

public:
    NetworkAccess();
    void findWord(QString word);

private slots:
    void finished(QNetworkReply* reply);

signals:
    void findInfo(Word* word);
    void findError(QString error);

private:
    void proceed();
    void procTranslation(QNetworkReply* reply);
    void procInfo(QNetworkReply* reply);
    QString word_;
    QNetworkAccessManager* mgr_;
    QNetworkReply* translation_;
    QNetworkReply* info_;
    QString trans_;
    QString descr_;
    QString examp_;
    QStringList anton_;
    QStringList synon_;
    bool isTranslate;
    bool isInfo;
};

#endif // NETWORKACCESS_H
