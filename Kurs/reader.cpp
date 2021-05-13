#include "reader.h"
#include <QtDebug>

Reader::Reader(QFile* file)
{
    file_ = file;
}

//Отправить запрос на получение общего списка слов для авто-дополнения при поиске.
//При каждом найденном слове, будет отправляться сигнал wordReady(word).
//При завершении чтения будет отправлен сигнал finished().
void Reader::getWords()
{
    if (!file_->open(QFile::ReadOnly)){
        qDebug() << "[READER] file error";
        emit finished();
        return;
    }

    QXmlStreamReader xml(file_);

    while(!xml.atEnd()){
        xml.readNext();

        if (xml.isStartDocument()) {
                    continue;
                }

        if (xml.isEndDocument()) {
                    break;
                }

        if(xml.isStartElement()){
            if(xml.name().toString() == "word"){
                QString word = xml.readElementText();
                emit wordReady(word);
                qDebug() << "[READER] emited word: " << word;

            }
        }
    }

    file_->close();
    qDebug() << "[READER] emiting finished() ";
    emit finished();
    return;
}
