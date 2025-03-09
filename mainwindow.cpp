#include "mainwindow.h"
#include "edittable.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QStatusBar>

MainWindow* mainWindowHandle;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    createMenus();
    createStatusBar();
    setContentsMargins(0,0,0,0);
    setMinimumHeight(500);
    setMinimumWidth(500);
    mainWindowHandle = this;
}

void MainWindow::createMenus() {

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *openAction = new QAction(tr("&Open"));
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(openAction);
    QAction *saveAction = new QAction(tr("&Save"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    fileMenu->addAction(saveAction);
    QAction *closeAction = new QAction(tr("&Close"));
    connect(closeAction, &QAction::triggered, this, &MainWindow::closeFile);
    fileMenu->addAction(closeAction);
    QAction *exitAction = new QAction(tr("E&xit"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);
}

void MainWindow::createStatusBar() {
    statusBar();
}


void MainWindow::openFile() {
    QString filename = QFileDialog::getOpenFileName(this, tr("select file"), "", tr("Tab Separated Values (*.tsv)"));
    if (filename.isEmpty()) {
        // user canceled open file
        return;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        lines << in.readLine();
    }
    file.close();

    EditTable* table = new EditTable(filename, this);
    table->loadData(lines);
    setCentralWidget(table);
}

void MainWindow::saveFile() {
    if (this->centralWidget() != nullptr) {
        ((EditTable*) this->centralWidget())->save();
    }
}

void MainWindow::closeFile() {
    if(this->centralWidget() != nullptr) {
        setCentralWidget(nullptr);
    }
}

void writeStatusText(QString message) {
    mainWindowHandle->statusBar()->showMessage(message);
}
