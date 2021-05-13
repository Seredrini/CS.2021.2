#include "selector.h"
#include <QtDebug>

Selector::Selector(QFile* file):
    file_(file), word_(""), access_(nullptr)
{
    writer_ = new FileWriter(file);
}

//Назначить слово, информация для которого будет искаться в методу getInfo.
//Нельзя запускать getInfo без назначенного слова.
void Selector::setWord(QString word)
{
    word_ = word;
}

//Поиск информации о слове word_.
//Проверяется весь файл data.xml. При нахождении слова отправляется сигнал infoReady(word)
//Если при работе с файлом возникла ошибка, отправляется сигнал finishedWithError(error)
//При завершении работы Селектора, отправляется сигнал finished.
//Если слова нет в файле data.xml, создается экземпляр QNetworkAccess,
//который отправляет запрос на сервер. При результате, Селектор получает результат в слоты
//getInfoFromAccess(word) или getErrorFromAccess.
//При получении ответа с сервера, производиться запись нового слова в файл.
void Selector::getInfo()
{
    if(word_ == ""){
        qDebug() << "[SELECTOR] null word selected";
        emit finished();
    }
    qDebug() << "[SELECTOR] starting search for: " << word_;
    if (!file_->open(QFile::ReadOnly)){
        qDebug() << "[SELECTOR] file error";
        emit finishedWithError("Unable to open the file");
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
                if(xml.readElementText() == word_){
                    QString desc = "";
                    QString examples = "";
                    QString translation = "";
                    QStringList ant;
                    QStringList syn;
                    xml.readNext();
                    xml.readNext();

                    while(!xml.isEndElement()){
                        if(xml.name().toString() == "desc"){
                            desc = xml.readElementText();
                        }
                        if(xml.name().toString() == "examples"){
                            examples = xml.readElementText();
                            examples.replace("{it}","<b>").replace("{/it}","</b>");
                            examples.replace("{ldquo}","\u201C").replace("{rdquo}","\u201D");
                        }
                        if(xml.name().toString() == "ant"){
                            QString antStr = xml.readElementText();
                            ant = antStr.split(",");
                        }
                        if(xml.name().toString() == "syn"){
                            QString synStr = xml.readElementText();
                            syn = synStr.split(",");
                        }
                        if(xml.name().toString() == "translation"){
                            translation = xml.readElementText();
                        }
                        xml.readNext();
                        xml.readNext();
                    }

                    Word* word = new Word(word_, desc, examples, translation, ant, syn);
                    emit infoReady(word);
                    qDebug() << "[SELECTOR] read info for: " << word_;
                    file_->close();
                    emit finished();
                    return;
                }
            }
        }
    }
    file_->close();
    qDebug() << "[SELECTOR] no info found for: " << word_;
    if(access_){
        delete access_;
        access_ = nullptr;
    }
    access_ = new NetworkAccess();
    connect(access_, &NetworkAccess::findInfo, this, &Selector::getInfoFromAccess);
    connect(access_, &NetworkAccess::findError, this, &Selector::getErrorFromAccess);
    access_->findWord(word_);
    return;
}

void Selector::getInfoFromAccess(Word *info)
{
    if(info->getWord() == word_){
        emit infoReady(info);
        writer_->writeWord(info);
    }
    else{
        qDebug() << "[SELECTOR] Access returned: " << info->getWord() << ", awaited: " << word_;
    }
    emit finished();
}

void Selector::getErrorFromAccess(QString error)
{
    emit finishedWithError(error);
    emit finished();
}
