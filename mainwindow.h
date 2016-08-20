#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QLocalServer>
#include <QFile>
#include <QDir>

#include "qjsonrpchttpserver.h"
#include "qjsonrpchttpclient.h"
#include "cocoservicemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    CocoServiceManager coco;
};

#endif // MAINWINDOW_H
