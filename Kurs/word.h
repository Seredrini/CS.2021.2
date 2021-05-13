#ifndef WORD_H
#define WORD_H

#include <QString>
#include <QStringList>

class Word
{

public:
    Word(QString word, QString desc,
         QString examples, QString translation,
         QStringList ant, QStringList syn);

    QString getWord();
    QString getDesc();
    QString getExamples();
    QString getTranslation();
    QStringList getAnt();
    QStringList getSyn();

private:
    QString word_;
    QString desc_;
    QString examples_;
    QString translation_;
    QStringList ant_;
    QStringList syn_;
};

#endif // WORD_H
