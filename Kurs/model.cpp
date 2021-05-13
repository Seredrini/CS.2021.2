#include "model.h"

Model::Model():
    QObject()
{
    file = new QFile("data.xml");

    reader = new Reader(file);
    reader->moveToThread(&threadR_);
    connect(reader, &Reader::wordReady, this, &Model::readWord);
    connect(&threadR_, &QThread::started, reader, &Reader::getWords);
    connect(reader, &Reader::finished, &threadR_, &QThread::quit);

    //Создание экземпляра класса Selector
    selector = new Selector(file);
    //Назначение выполнения функций объекта selector в отдельном потоке threadS_
    selector->moveToThread(&threadS_);
    //Назначение сигналов и слотов, для получения найденных слов и корректного
    //завершения потока
    connect(selector, &Selector::infoReady, this, &Model::readInfo);
    connect(&threadS_, &QThread::started, selector, &Selector::getInfo);
    connect(selector, &Selector::finished, &threadS_, &QThread::quit);
    connect(selector, &Selector::finishedWithError, this, &Model::readWordError);

}

Model::~Model(){
    threadR_.quit();
    threadR_.wait();
    threadS_.quit();
    threadS_.wait();
}

//Запросить у Reader общий список слов для авто-дополнения в поиске
void Model::startWordsReading(){
    if(threadR_.isRunning()){
        threadR_.quit();
        threadR_.wait();
    }
    threadR_.start();
}

//Добавить в историю слов определенное слово, и обновить информацию в MainWindow
void Model::readWord(QString word){
    words_.push_back(word);
    emit updateWords();
}

//Добавить в историю информации о словах определенную информацию и обновить информацию в MainWindow
void Model::readInfo(Word *word)
{
    wordsInfo_.insert(wordsInfo_.begin(), word);
    emit updateCurrentWord();

}

//Обработка ошибки, возникшей при чтении слова
void Model::readWordError(QString error)
{
    emit errorInSelection(error);
}

QStringList Model::getWords(){
    return words_;
}

std::vector<Word*> Model::getHistory()
{
    return wordsInfo_;
}

//Получить слово, которое в данный момент должно находиться на экране
Word* Model::getCurrentWord()
{
    return wordsInfo_[0];
}

//Получить информацию о определенном слове
void Model::getWordInfo(QString word){
    unsigned long long i = 0;
    while(i < wordsInfo_.size()){
        if(wordsInfo_[i]->getWord() == word){
            Word* word = wordsInfo_[i];
            wordsInfo_.erase(wordsInfo_.begin() + i);
            wordsInfo_.insert(wordsInfo_.begin(), word);
            qDebug() << "[MODEL] found in history: " << word;
            emit updateCurrentWord();
            return;
        }
        i++;
    }
    if(threadS_.isRunning()){
        threadS_.quit();
        threadS_.wait();
    }
    selector->setWord(word);
    threadS_.start();
}

