#include "filewriter.h"

FileWriter::FileWriter(QFile* file):
    file_(file)
{}

void FileWriter::writeWord(Word* word)
{
    if (file_->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QDomDocument document;

        if (document.setContent(file_))
        {
            file_->close();

            QDomElement docEle = document.documentElement();
            QDomNodeList elements = docEle.elementsByTagName("root");

            QDomElement el = document.createElement( "el" );

            QDomElement wordtitle = document.createElement("word");
            QDomText wordText = document.createTextNode(word->getWord());

            QDomElement desc = document.createElement("desc");
            QDomText descText = document.createTextNode(word->getDesc());

            QDomElement examples = document.createElement("examples");
            QDomText examplesText = document.createTextNode(word->getExamples());

            QDomElement translation = document.createElement("translation");
            QDomText translationText = document.createTextNode(word->getTranslation());

            QDomElement ant = document.createElement("ant");
            QDomText antText = document.createTextNode(word->getAnt().join(','));

            QDomElement syn = document.createElement("syn");
            QDomText synText = document.createTextNode(word->getSyn().join(','));

            wordtitle.appendChild(wordText);
            desc.appendChild(descText);
            examples.appendChild(examplesText);
            translation.appendChild(translationText);
            ant.appendChild(antText);
            syn.appendChild(synText);

            el.appendChild(wordtitle);
            el.appendChild(desc);
            el.appendChild(examples);
            el.appendChild(translation);
            el.appendChild(ant);
            el.appendChild(syn);

            docEle.appendChild(el);

            QFile* outFile = file_;
            if(outFile->open( QIODevice::WriteOnly | QIODevice::Text ))
            {
                QTextStream stream(outFile);
                stream << document.toString();

                outFile->close();

                qDebug() << "[FILEWRITER] new record added for: " << word->getWord();
            }
            else
            {
                qDebug() << "[FILEWRITER] failed to add new record added for: " << word->getWord();
            }
        }
    }
}
