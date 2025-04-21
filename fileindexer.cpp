#include "FileIndexer.h"
#include <QDirIterator>
#include <QDebug>

FileIndexer::FileIndexer(QObject *parent) : QObject(parent)
{
}

void FileIndexer::startIndexing()
{
    QStringList files;
    QDirIterator it("/home", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        files << it.next();
    }
    emit filesIndexed(files);
}
