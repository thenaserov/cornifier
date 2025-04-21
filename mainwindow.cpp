#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "fileindexer.h"
#include <QVBoxLayout>
#include <QDirIterator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new QStringListModel(this)),
    indexer(new FileIndexer),
    indexingThread(new QThread(this))
{

    // ui = new Ui::MainWindow;
    ui->setupUi(this);
    ui->resultListView->setModel(model);
    // Thread setup
    indexer->moveToThread(indexingThread);
    connect(indexingThread, &QThread::started, indexer, &FileIndexer::startIndexing);
    connect(indexer, &FileIndexer::filesIndexed, this, &MainWindow::onFilesIndexed);
    connect(this, &MainWindow::destroyed, indexingThread, &QThread::quit);
    connect(indexingThread, &QThread::finished, indexer, &QObject::deleteLater);

    indexingThread->start();

    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
}

MainWindow::~MainWindow()
{
    indexingThread->quit();
    indexingThread->wait();
}

void MainWindow::onFilesIndexed(const QStringList &files)
{
    allFiles = files;
    model->setStringList(allFiles);
}

void MainWindow::onSearchTextChanged(const QString &text)
{
    QStringList filtered;
    for (const QString &file : allFiles)
    {
        if (file.contains(text, Qt::CaseInsensitive))
            filtered << file;
    }
    model->setStringList(filtered);
}
