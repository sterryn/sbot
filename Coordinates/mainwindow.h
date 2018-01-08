#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filehandlers.h"
#include "licdialog.h"
#include <QMainWindow>
#include <QtSql>
#include <QDesktopWidget>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QTableWidget>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString workdir = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QString(), QStandardPaths::LocateDirectory) + "Coordinates/";
    QString dbName = workdir + "coordinates.sqlite";

public slots:
    void createUserVars();
    void opendb();
    void closedb();
    void showTable();

private slots:
    void on_pushButtonAddCoordinates_clicked();

    void on_pushButtonUpdate_clicked();

    void on_pushButtonDelete_clicked();

    void on_lineEditSearch_textChanged(const QString &arg1);

    void on_actionExit_triggered();

    void on_tableWidget_cellClicked(int row);

    void on_actionReload_triggered();

    void on_actionLicense_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    fileHandlers myfiles;
    licDialog myLicense;
};

#endif // MAINWINDOW_H
