#include "word.h"

Word::Word(QString word, QString desc, QString examples, QString translation, QStringList ant, QStringList syn):
    word_(word), desc_(desc), examples_(examples), translation_(translation), ant_(ant), syn_(syn)
{
}

QString Word::getDesc()
{
    return desc_;
}

QString Word::getWord()
{
    return word_;
}

QString Word::getExamples()
{
    return examples_;
}

QString Word::getTranslation()
{
    return translation_;
}

QStringList Word::getAnt()
{
    return ant_;
}

QStringList Word::getSyn()
{
    return syn_;
}
