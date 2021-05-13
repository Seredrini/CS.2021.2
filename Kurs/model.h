#ifndef MODEL_H
#define MODEL_H

#include <QtXml>
#include "word.h"
#include "selector.h"
#include "reader.h"

class Model : public QObject
{
    Q_OBJECT

public:
    Model();
    ~Model();
    QStringList getWords();
    std::vector<Word*> getHistory();
    Word* getCurrentWord();
    void getWordInfo(QString word);
    void startWordsReading();

signals:
    void updateWords();
    void updateCurrentWord();
    void errorInSelection(QString error);

public slots:
    void readWord(QString word);
    void readInfo(Word* word);
    void readWordError(QString error);

private:
    QFile* file;
    Selector* selector;
    Reader* reader;
    std::vector<Word*> wordsInfo_;
    QStringList words_;
    QThread threadR_;
    QThread threadS_;
};

#endif // MODEL_H
