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
    QAction *saveAction = new QAction(tr("&Save"));
    closeAction = new QAction(tr("&Close"));
    QAction *exitAction = new QAction(tr("E&xit"));

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(closeAction, &QAction::triggered, this, &MainWindow::closeFile);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(closeAction);
    fileMenu->addAction(exitAction);

    closeAction->setEnabled(false);
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
    closeAction->setEnabled(true);
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
    closeAction->setEnabled(false);
}

void writeStatusText(QString message) {
    mainWindowHandle->statusBar()->showMessage(message);
}
