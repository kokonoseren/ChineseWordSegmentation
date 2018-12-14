#ifndef WORDSEGMENTATION_H
#define WORDSEGMENTATION_H

//#include <QMainWindow>
#include <iostream>
#include <vector>
#include "dictionary.h"
#include "sentencegraph.h"
using namespace std;
/*
namespace Ui {
class WordSegmentation;
}

Class Dictionary;

Class

class WordSegmentation : public QMainWindow
{
    Q_OBJECT

public:
    explicit WordSegmentation(QWidget *parent = 0);
    ~WordSegmentation();

    void shortest_path();
    void output_result();

private:
    Ui::WordSegmentation *ui;

};
*/

class WordSegmentation
{
public:
    WordSegmentation();
    ~WordSegmentation();

    void show();
    void shortest_path(SentenceGraph graph);

private:
    Dictionary * _dict;
};

#endif // WORDSEGMENTATION_H
