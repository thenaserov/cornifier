#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QListView>
#include <QStringListModel>
#include <QThread>
#include <QFileSystemWatcher>

class FileIndexer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSearchTextChanged(const QString &text);
    void onFilesIndexed(const QStringList &files);

private:
    Ui::MainWindow *ui;

    QStringListModel *model;
    QStringList allFiles;

    FileIndexer *indexer;
    QThread *indexingThread;
};

#endif // MAINWINDOW_H
