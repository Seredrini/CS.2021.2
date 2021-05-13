#ifndef SELECTOR_H
#define SELECTOR_H

#include <QString>
#include <QtXml>
#include "word.h"
#include "networkaccess.h"
#include "filewriter.h"

class Selector : public QObject
{
    Q_OBJECT

public:
    Selector(QFile* file);
    void setWord(QString word);
private:
    QFile* file_;
    QString word_;
    NetworkAccess* access_;
    FileWriter* writer_;

public slots:
    void getInfo();
    void getInfoFromAccess(Word* info);
    void getErrorFromAccess(QString error);

signals:
    void infoReady(Word* info);
    void finished();
    void finishedWithError(QString error);
};

#endif // SELECTOR_H
