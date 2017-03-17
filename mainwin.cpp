#include "mainwin.h"

mainWin::mainWin(QWidget *parent)
    : QWidget(parent)
{
    this->setMinimumSize(400,200);
    mainLayiut=new QVBoxLayout(this);
    all=new QLabel("All lines in this project: ");
    allV=new QLabel();
    allValue=0;
    goodCod=new QLabel("Utility lines in this project:");
    goodV=new QLabel();
    goodCodValue=0;
    OpenB=new QPushButton("Open Folder",this);
    QHBoxLayout *lout=new QHBoxLayout();
    lout->addWidget(all);
    lout->addWidget(allV);
    mainLayiut->addLayout(lout);
    lout=new QHBoxLayout();
    lout->addWidget(goodCod);
    lout->addWidget(goodV);
    mainLayiut->addLayout(lout);
    mainLayiut->addWidget(OpenB);
    list.push_back("*.cpp");
    list.push_back("*.h");
    list.push_back("*.cs");
    list.push_back("*.java");
    list.push_back("*.qml");
    connect(OpenB,SIGNAL(clicked(bool)),this,SLOT(openFol()));
}
bool mainWin::testLineComent(const QString &string)
{
    int temp=string.indexOf(QRegExp("[^\s][^\s]"));
    return (temp==-1||string.mid( temp,2)=="//");
}
QPair<int,int> mainWin::WriteLines(const QFileInfo &info)
{
    QFile f(info.absoluteFilePath());
    QPair<int,int> result;result.first=0;result.second=0;
    if(f.open(QIODevice::ReadOnly))
    {
        QString tempString="";
        QTextStream stream(&f);
        bool longComent=false;
        while(!stream.atEnd())
        {
            tempString= stream.readLine();
            if(tempString.indexOf("/*")!=-1)
                longComent=true;
            if(!longComent&&!testLineComent(tempString))
                result.first++;
            result.second++;
            if(tempString.indexOf("*/")!=-1)
                longComent=false;
        }
    }
    else
    {
        QMessageBox::information(this,"Read file Error","file "+info.absoluteFilePath()+"is not ready");
    }
    f.close();
    return result;
}
void mainWin::DirectFind(const QString& str)
{
    QDir d(str);
    QPair<int,int>  temp;
    d.entryList();
    for(QString st:d.entryList(QDir::Dirs))
        if(st!="."&&st!="..")
            DirectFind(str+"/"+st);
    for(QFileInfo inf:d.entryInfoList(list))
    {
        temp=WriteLines(inf);
        goodCodValue+= temp.first;
        allValue+=temp.second;
    }
    allV->setText(QString::number(allValue));
    goodV->setText(QString::number(goodCodValue));

}
void mainWin::openFol()
{
    DirectFind(QFileDialog::getExistingDirectory());
    goodCodValue=0;
    allValue=0;

}
mainWin::~mainWin()
{

}
