#include "filehandlers.h"

fileHandlers::fileHandlers()
{

}

void fileHandlers::createFile(QString fileName)
{
    QFile mfile(fileName);
    if (!mfile.exists())
    {
        if(!mfile.open(QFile::ReadWrite)) showFileErrors(mfile.errorString());
        mfile.close();
    }
}

QStringList fileHandlers::readFile(QString fileName)
{
    QStringList str;
    QFile mfile(fileName);
    QTextStream in(&mfile);
    if (!mfile.open(QFile::ReadOnly)) showFileErrors(mfile.errorString());
    while (!in.atEnd())
    {
        QString line = in.readLine();
        str.append(line);
    }
    mfile.close();
    return str;
}

void fileHandlers::writeToFile(QString fileName, QString content)
{
    QFile mfile(fileName);
    QTextStream out(&mfile);
    if (!mfile.open(QFile::ReadWrite)) showFileErrors(mfile.errorString());
    out << content;
    mfile.flush();
    mfile.close();
}

void fileHandlers::appendToFile(QString fileName, QString content)
{
    QFile mfile(fileName);
    QTextStream out(&mfile);
    if (!mfile.open(QFile::ReadWrite | QFile::Append)) showFileErrors(mfile.errorString());
    out << content;
    mfile.flush();
    mfile.close();
}

void fileHandlers::truncateFile(QString fileName)
{
    QFile mfile(fileName);
    if (mfile.exists()) mfile.open(QFile::Truncate);
    else showFileErrors(mfile.errorString());
}

void fileHandlers::showFileErrors(QString errorMsg)
{
    QMessageBox msg;
    msg.setWindowTitle("Error");
    msg.setText(errorMsg);
    msg.exec();
    qFatal("0");
}

void fileHandlers::deleteFile(QString fileName)
{
    QFile mfile(fileName);
    if (mfile.exists()) mfile.deleteLater();
    else showFileErrors(mfile.errorString());
}

