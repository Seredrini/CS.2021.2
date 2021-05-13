#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsBlurEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    model = new Model();
    connect(model, &Model::updateWords, this, &MainWindow::updateWords);
    connect(model, &Model::updateCurrentWord, this, &MainWindow::updateCurrentWord);
    connect(model, &Model::errorInSelection, this, &MainWindow::displayError);

    showHistory = false;
    showAddInfo = false;
    ui->setupUi(this);
    this->setWindowTitle("Thesaurus");
    QIcon appIcon("app.png");
    this->setWindowIcon(appIcon);
    setHistoryVisible(showHistory);
    setAddInfoVisible(showAddInfo);

    QIcon searchIcon("magnifier.png");
    ui->lineEdit->setClearButtonEnabled(true);
    ui->lineEdit->addAction(searchIcon, QLineEdit::LeadingPosition);
    ui->lineEdit->setPlaceholderText("Искать...");

    ui->desc->setWordWrap(true);
    ui->examples->setWordWrap(true);
    ui->translation->setWordWrap(true);

    model->startWordsReading();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Обновление общего списка слов, который используется для авто дополнения при поиске
void MainWindow::updateWords()
{
    QStringList words = model->getWords();

    QCompleter *completer = new QCompleter(words, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(completer);
}

//Показ информации о определенном слове, запрошенном из Model
void MainWindow::updateCurrentWord()
{
    Word* word = model->getCurrentWord();
    ui->word->setText(word->getWord());
    QString desc = word->getDesc();

    ui->desc->setText(desc);
    ui->examples->setText(word->getExamples());
    ui->translation->setText(word->getTranslation());

    ui->listWidget_Ant->clear();
    QStringList ant = word->getAnt();
    for(long long i = 0; i < ant.size(); i++){
        if(ant[i] != "")
            ui->listWidget_Ant->addItem(ant[i]);
    }

    ui->listWidget_Syn->clear();
    QStringList syn = word->getSyn();
    for(long long i = 0; i < syn.size(); i++){
        if(syn[i] != "")
            ui->listWidget_Syn->addItem(syn[i]);
    }

    std::vector<Word*> history = model->getHistory();
    ui->listWidget->clear();
    for(unsigned long long i = 0; i < history.size(); i++){
        ui->listWidget->addItem(history[i]->getWord());
    }

    showHistory = true;
    setHistoryVisible(showHistory);

    showAddInfo = true;
    setAddInfoVisible(showAddInfo);
}

//Вывод, происходящий при возникшей ошибке
void MainWindow::displayError(QString error)
{
    showAddInfo = false;
    setAddInfoVisible(showAddInfo);
    ui->word->setText("Error...");
    ui->desc->setText(error);
}

void MainWindow::on_lineEdit_editingFinished()
{
    selectWord(ui->lineEdit->text());
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    selectWord(item->text());
}

//Запросить определенное слово из Model
void MainWindow::selectWord(QString word)
{
    word = word.toLower();
    if(word == "") return;
    qDebug() << "[UI] selected word: " << word;
    showAddInfo = false;
    setAddInfoVisible(showAddInfo);
    ui->word->setText("Loading...");
    ui->desc->setText("Waiting for server response");
    model->getWordInfo(word);
}

//Видимость истории поиска
void MainWindow::setHistoryVisible(bool visible)
{
    ui->line->setVisible(visible);
    ui->verticalWidget->setVisible(visible);
}

//Видимость доп. информации- перевода, примеров, антонимов, синонимов
void MainWindow::setAddInfoVisible(bool visible)
{
    ui->line_2->setVisible(visible);
    ui->horizontalWidget_synant->setVisible(visible);
    ui->examples->setVisible(visible);
    ui->examplesTitle->setVisible(visible);
    ui->translation->setVisible(visible);
    ui->translationTitle->setVisible(visible);
}


void MainWindow::on_listWidget_Syn_itemClicked(QListWidgetItem *item)
{
    selectWord(item->text());
}

void MainWindow::on_listWidget_Ant_itemClicked(QListWidgetItem *item)
{
    selectWord(item->text());
}
