#include "widget.h"
#include "ui_widget.h"
#include <QProcess>
#include <QFileDialog>
#include <QDirIterator>
#include <QDebug>
#include<QFile>
#include <fileapi.h>


/*
 Здравствуйте. Не совсем понял, как в этой программе исполнить параллеризм, так как все действия происходят по кнопкам и как таковые потоки тут отсутствуют. Могу показать и доказать свои знания в этой области на других примерах.
 К сожалению, не получился красивый вывод дерева каталога из-за особенностей выбранного метода обхода каталога.
  */
using namespace std;
QString dir;
static int catalog=0;
static int fileTXT=0;
static QList<int> sizes;
static QList<int> countElems;
static QList<QString> extensions;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_openButton_clicked()
{
    ui->textEdit->clear();
    dir = QFileDialog::getExistingDirectory(this,
                               QString::fromUtf8("Открыть папку"),
                               "C:\\demo\\testFolders\\Folder",
                               QFileDialog::ShowDirsOnly
                               | QFileDialog::DontResolveSymlinks);
     ui->textEdit->append("Выбранная папка: "+dir);

}
int Widget::extensionExist(QString Filename){
    for(int i=0;i<extensions.count();i++){
        if(extensions[i]==Filename)
            return i;
    }
    return -1;
}
int Widget::listSumm(QList<int> index){
    int counting=0;
    for(int i=0;i<index.count();i++){
        counting=counting+index[i];
    }
    return counting;
    }

void Widget::showFiles(QString sDir){
    QDir dir(sDir);
        QFileInfoList list = dir.entryInfoList();
        for (int iList=0;iList<list.count();iList++)
        {
            QFileInfo info = list[iList];

            QString sFilePath = info.filePath();
             if (info.isDir())
            {
                // recursive
                if (info.fileName()!=".." && info.fileName()!=".")
                {
                     ui->textEdit->append("-"+info.fileName());
                    showFiles(sFilePath);
                }
            }
            else
            {
                ui->textEdit->append(info.fileName());
            }
        }
}
void Widget::showStatistic(QString sDir)
{
    QDir dir(sDir);
        QFileInfoList list = dir.entryInfoList();
        for (int iList=0;iList<list.count();iList++)
        {
            QFileInfo info = list[iList];

            QString sFilePath = info.filePath();
            if (info.isDir())
            {
                // recursive
                if (info.fileName()!=".." && info.fileName()!=".")
                {
                    catalog=catalog+1;
                    showStatistic(sFilePath);
                }
            }
            else
            {
              int g=extensionExist(info.suffix());
              if(g==-1){
                  extensions.push_back(info.suffix());
                  QFile file(info.filePath());
                  sizes.push_back(file.size());
countElems.push_back(1);
              }
              else{
                  QFile file(info.filePath());
                  sizes[g]=sizes[g]+file.size();
                  countElems[g]=countElems[g]++;
              }
                fileTXT=fileTXT+1;
       }
}
}
void Widget::on_statisticButton_clicked()
{
ui->textEdit->clear();

catalog=0;
sizes.clear();
countElems.clear();
extensions.clear();
showStatistic(dir);
for(int i=0;i<extensions.count();i++){

    ui->textEdit->append("Average size of files "+extensions[i]+"= "+QString::number(sizes[i]/countElems[i]/1024)+"KB");
     ui->textEdit->append("Number of files "+extensions[i]+"= "+QString::number(countElems[i]));
}

ui->textEdit->append("Summ of elements= "+QString::number(listSumm(sizes)/1024)+"KB");
ui->textEdit->append("Overall number of elements= "+QString::number(listSumm(countElems)));
 ui->textEdit->append("Overall number of folder= "+QString::number(catalog));
}

void Widget::on_treeButton_clicked()
{
    ui->textEdit->clear();
    showFiles(dir);
}
