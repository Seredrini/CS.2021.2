#include "networkaccess.h"

NetworkAccess::NetworkAccess():
    translation_(nullptr), info_(nullptr)
{
    mgr_ = new QNetworkAccessManager(this);
    connect(mgr_, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
}

//Запуск поиска для определенного слова. При получении ответа будет вызван слот finished.
void NetworkAccess::findWord(QString word)
{
    isTranslate = false;
    isInfo = false;

    if(translation_){
        translation_->abort();
        delete translation_;
        translation_ = nullptr;
    }
    if(info_){
        info_->abort();
        delete info_;
        info_ = nullptr;
    }
    word_ = word;
    qDebug() << "[NETWORK] Starting search for: " << word_;
    const QUrl url(QStringLiteral("https://google-translate1.p.rapidapi.com/language/translate/v2"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("content-type", "application/x-www-form-urlencoded");
    request.setRawHeader("accept-encoding", "application/gzip");
    request.setRawHeader("x-rapidapi-key", "c869522554msha157e3a4d28534fp141526jsn2222f0c3b46e");
    request.setRawHeader("x-rapidapi-host", "google-translate1.p.rapidapi.com");

    QString str = "q="+word_+"&target=ru&source=en";
    QByteArray data = str.toUtf8();

    translation_ = mgr_->post(request, data);

    qDebug() << "[NETWORK] sent translation post request for: " << word_;

    info_ = mgr_->get(QNetworkRequest(QUrl("https://www.dictionaryapi.com/api/v3/references/ithesaurus/json/" + word_ + "?key=34ca849b-7651-473d-b264-3f5707efaff9")));

    qDebug() << "[NETWORK] sent info get request for: " << word_;
}

void NetworkAccess::finished(QNetworkReply* reply)
{
    if (reply == translation_) procTranslation(reply);
    else if (reply == info_) procInfo(reply);
}

//финальная функция, которая собирает вместе ответы с серверов
void NetworkAccess::proceed()
{
    if(isTranslate && isInfo){
        if(descr_ != "" &&
           examp_ != "" &&
           trans_ != "" )
        {
            Word* answer = new Word(word_, descr_, examp_, trans_, anton_, synon_);
            emit findInfo(answer);
        }
        else{
            emit findError("No information for this word");
        }
    }
}

//обработка ответа с сервера переводов
void NetworkAccess::procTranslation(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "[NETWORK] Got translation for: " << word_;

        //Получение строки ответа с сервера
        QString content = QString::fromUtf8(reply->readAll());
        //Преобразование строки в json документ
        QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
        //Преобразование документа в объект, для непосредственной работы
        QJsonObject jObject = doc.object();
        //Дессереализация
        trans_ = "[Russian] - " + jObject["data"].toObject()["translations"].toArray()[0].toObject()["translatedText"].toString();
        isTranslate = true;
        proceed();
    }
    else
    {
        QString err = reply->errorString();
        qDebug() << "[NETWORK] Error in translation reply: "<< err;
        emit findError("Failure in connection");
    }
    reply->deleteLater();
}

//обработка ответа с сервера информации о слове
void NetworkAccess::procInfo(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "[NETWORK] Got info for: " << word_;

        QString content = QString::fromUtf8(reply->readAll());
        content.remove(0, 1);
        content.remove(content.size()-1, 1);
        int extra = content.indexOf(",{\"meta\"");
        if (extra >= 1) content.remove(extra, content.size()-extra);
        QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());

        QJsonObject jObject = doc.object();

        descr_ = jObject["def"].toArray()[0].toObject()["sseq"].toArray()[0].toArray()[0].toArray()[1].toObject()["dt"].toArray()[0].toArray()[1].toString();
        examp_ = jObject["def"].toArray()[0].toObject()["sseq"].toArray()[0].toArray()[0].toArray()[1].toObject()["dt"].toArray()[1].toArray()[1].toArray()[0].toObject()["t"].toString();
        examp_.replace("{it}","<b>").replace("{/it}","</b>");
        examp_.replace("{ldquo}","\u201C").replace("{rdquo}","\u201D");
        QJsonArray anton = jObject["meta"].toObject()["ants"].toArray()[0].toArray();
        QJsonArray synon = jObject["meta"].toObject()["syns"].toArray()[0].toArray();

        anton_ = QStringList();
        foreach (const QJsonValue & v, anton)
                anton_ += v.toString();

        synon_ = QStringList();
        foreach (const QJsonValue & v, synon)
                synon_ += v.toString();

        isInfo = true;
        proceed();
    }
    else
    {
        QString err = reply->errorString();
        qDebug() << "[NETWORK] Error in info reply: "<< err;
        emit findError("Failure in connection");
    }
    reply->deleteLater();
}
