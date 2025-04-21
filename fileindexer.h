#ifndef FILEINDEXER_H
#define FILEINDEXER_H

#include <QObject>
#include <QStringList>

class FileIndexer : public QObject
{
    Q_OBJECT
public:
    explicit FileIndexer(QObject *parent = nullptr);

signals:
    void filesIndexed(const QStringList &files);

public slots:
    void startIndexing();
};

#endif // FILEINDEXER_H
