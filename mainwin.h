#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPair>
class mainWin : public QWidget
{
    Q_OBJECT
private:
    void DirectFind(const QString&);
    QLabel *state;
    QPair<int,int> WriteLines(const QFileInfo& info);
    bool testLineComent(const QString&string);
    QVBoxLayout *mainLayiut;
    QPushButton *OpenB;
    QStringList list;
    QLabel *all,*allV,*goodCod,*goodV;
    int goodCodValue,allValue;
private slots:
    void openFol();
public:
    mainWin(QWidget *parent = 0);
    ~mainWin();
};

#endif // MAINWIN_H
