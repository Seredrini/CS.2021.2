#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QTextStream>
#include <QDebug>
#include "word.h"

class FileWriter
{
public:
    FileWriter(QFile* file);
    void writeWord(Word* word);

private:
    QFile* file_;

};

#endif // FILEWRITER_H
