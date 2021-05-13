#ifndef READER_H
#define READER_H

#include <QString>
#include <QtXml>

class Reader : public QObject
{
    Q_OBJECT

public:
    Reader(QFile* file);

private:
    QFile* file_;

public slots:
    void getWords();

signals:
    void wordReady(QString word);
    void finished();
};

#endif // READER_H
