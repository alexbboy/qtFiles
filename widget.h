#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QDir>
#include <windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    int IsNowName(QString Filename);
    int indexCount(QList<int> list);
    void FileObjects(QString Path);
    void on_openButton_clicked();
void scanDir(QString dir);
    void on_statisticButton_clicked();

    void on_treeButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
