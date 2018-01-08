#ifndef FILEHANDLERS_H
#define FILEHANDLERS_H
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>


class fileHandlers
{
public:
    fileHandlers();

public slots:
    void createFile(QString fileName);
    QStringList readFile(QString fileName);
    void writeToFile(QString fileName, QString content);
    void appendToFile(QString fileName, QString content);
    void truncateFile(QString fileName);
    void showFileErrors(QString errorMsg);
    void deleteFile(QString fileName);



};

#endif // FILEHANDLERS_H
