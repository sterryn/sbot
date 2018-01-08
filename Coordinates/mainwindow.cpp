#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableView>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),qApp->desktop()->availableGeometry()));
    createUserVars();
    opendb();
    showTable();
}

MainWindow::~MainWindow()
{
    closedb();
    delete ui;
}

void MainWindow::createUserVars()
{
    QDir mdir(workdir);
    if (!mdir.exists()) mdir.mkpath(workdir);
    myfiles.createFile(dbName);
}

void MainWindow::opendb()
{
    db.setDatabaseName(dbName);
    if (!db.open())
    {
        myfiles.showFileErrors(db.lastError().text());
        qFatal("0");
    }
    QSqlQuery query;
    QString sql ="CREATE TABLE IF NOT EXISTS 'places' ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
                "Name TEXT,"
                "X TEXT,"
                "Y TEXT,"
                "Z TEXT,"
                "Radius TEXT,"
                "Remarks TEXT"
            ")";
  if (!query.exec(sql)) myfiles.showFileErrors(query.lastError().text());
}

void MainWindow::closedb()
{
    db.close();
}

void MainWindow::showTable()
{
    QSqlQuery query;
    if (!query.exec("SELECT COUNT(id) as numRows FROM places")) myfiles.showFileErrors(query.lastError().text());
    query.first();
    int numRows = query.value(0).toInt();
    if (!query.exec("SELECT * FROM places")) myfiles.showFileErrors(query.lastError().text());
    ui->tableWidget->setRowCount(numRows);
    ui->tableWidget->setColumnCount(7);
    QStringList myHeader;
    myHeader << "id" << "Name" << "X" << "Y" << "Z" << "Radius" << "Remarks";
    ui->tableWidget->setHorizontalHeaderLabels(myHeader);
    ui->tableWidget->setColumnHidden(0, true);
    ui->tableWidget->setStyleSheet("QHeaderView::section { background-color:orange }");
    ui->tableWidget->resizeColumnsToContents();
    numRows = 0;
    while(query.next())
    {
        ui->tableWidget->setItem(numRows,0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(numRows,1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(numRows,2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(numRows,3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(numRows,4, new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(numRows,5, new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidget->setItem(numRows,6, new QTableWidgetItem(query.value(6).toString()));
        numRows++;
    }
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_pushButtonAddCoordinates_clicked()
{
    QString naam = ui->lineEditName->text(); ui->lineEditName->setText("");
    QString x =ui->lineEditNameX->text(); ui->lineEditNameX->setText("");
    QString y =ui->lineEditNameY->text(); ui->lineEditNameY->setText("");
    QString z =ui->lineEditNameZ->text(); ui->lineEditNameZ->setText("");
    QString radius =ui->lineEditRadius->text(); ui->lineEditRadius->setText("");
    QString remarks = ui->textEditRemarks->toPlainText(); ui->textEditRemarks->setText("");
    QString sql = "INSERT INTO places (Name, X, Y, Z, Radius, Remarks) VALUES ("
                  "'"+naam+"',"
                  "'"+x+"',"
                  "'"+y+"',"
                  "'"+z+"',"
                  "'"+radius+"',"
                  "'"+remarks+"')";
    QSqlQuery query;
    if (!query.exec(sql)) myfiles.showFileErrors(query.lastError().text());
    showTable();
}

void MainWindow::on_pushButtonUpdate_clicked()
{
    QString id, name, x, y, z, radius, remarks, sql;
    id = ui->lineEditNameEditId->text();ui->lineEditNameEditId->setText("");
    name = ui->lineEditNameEditName->text();ui->lineEditNameEditName->setText("");
    x = ui->lineEditNameEditX->text();ui->lineEditNameEditX->setText("");
    y = ui->lineEditNameEditY->text();ui->lineEditNameEditY->setText("");
    z = ui->lineEditNameEditZ->text();ui->lineEditNameEditZ->setText("");
    radius = ui->lineEditEditRadius->text();ui->lineEditEditRadius->setText("");
    remarks = ui->textEditRemarksEdit->toPlainText();ui->textEditRemarksEdit->setText("");
    sql = "UPDATE places set Name='"+name+"', X='"+x+"', Y='"+y+"', Z='"+z+"', Radius='"+radius+"', Remarks='"+remarks+"' WHERE id='"+id+"'";
    QSqlQuery query;
    if (!query.exec(sql)) myfiles.showFileErrors(query.lastError().text());
    showTable();
}

void MainWindow::on_pushButtonDelete_clicked()
{
    QString sql = "DELETE FROM places WHERE id='" + ui->lineEditNameEditId->text() + "'";
    ui->lineEditNameEditId->setText("");
    ui->lineEditNameEditName->setText("");
    ui->lineEditNameEditX->setText("");
    ui->lineEditNameEditY->setText("");
    ui->lineEditNameEditZ->setText("");
    ui->lineEditEditRadius->setText("");
    ui->textEditRemarksEdit->setText("");
    QSqlQuery query;
    if (!query.exec(sql)) myfiles.showFileErrors(query.lastError().text());
    showTable();
}

void MainWindow::on_lineEditSearch_textChanged(const QString &arg1)
{
    QSqlQuery query;
    if (!query.exec("SELECT COUNT(id) as numRows FROM places WHERE Name LIKE '%"+arg1+"%'")) myfiles.showFileErrors(query.lastError().text());
    query.first();
    int numRows = query.value(0).toInt();
    QString sql = "SELECT * from places WHERE Name LIKE '%"+arg1+"%'";

    if (!query.exec(sql)) myfiles.showFileErrors(query.lastError().text());
    ui->tableWidget->setRowCount(numRows);
    ui->tableWidget->setColumnCount(7);
    QStringList myHeader;
    myHeader << "id" << "Name" << "X" << "Y" << "Z" << "Radius" << "Remarks";
    ui->tableWidget->setHorizontalHeaderLabels(myHeader);
    ui->tableWidget->setColumnHidden(0, true);
    ui->tableWidget->setStyleSheet("QHeaderView::section { background-color:orange }");
    ui->tableWidget->resizeColumnsToContents();
    numRows = 0;
    while(query.next())
    {
        ui->tableWidget->setItem(numRows,0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(numRows,1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(numRows,2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(numRows,3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(numRows,4, new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(numRows,5, new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidget->setItem(numRows,6, new QTableWidgetItem(query.value(6).toString()));
        numRows++;
    }
    ui->tableWidget->resizeColumnsToContents();

}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_tableWidget_cellClicked(int row)
{
    QString id = ui->tableWidget->item(row,0)->text();
    QString sql = "SELECT * FROM places where id='"+id+"'";
    QSqlQuery query;
    if (!query.exec(sql)) myfiles.showFileErrors(query.lastError().text());
    query.first();
    ui->lineEditNameEditId->setText(query.value(0).toString());
    ui->lineEditNameEditName->setText(query.value(1).toString());
    ui->lineEditNameEditX->setText(query.value(2).toString());
    ui->lineEditNameEditY->setText(query.value(3).toString());
    ui->lineEditNameEditZ->setText(query.value(4).toString());
    ui->lineEditEditRadius->setText(query.value(5).toString());
    ui->textEditRemarksEdit->setText(query.value(6).toString());

}

void MainWindow::on_actionReload_triggered()
{
    ui->lineEditSearch->setText("");
    showTable();
}

void MainWindow::on_actionLicense_triggered()
{
    myLicense.setModal(true);
    myLicense.exec();
}
