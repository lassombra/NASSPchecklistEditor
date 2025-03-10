#include "mainwindow.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    initializeTabControl();
    createMenus();
    createStatusBar();
    setContentsMargins(0,0,0,0);
    setMinimumHeight(500);
    setMinimumWidth(500);
}

void MainWindow::createMenus() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *openAction = new QAction(tr("&Open..."));
    QAction *saveAction = new QAction(tr("&Save"));
    QAction *saveAsAction = new QAction(tr("Save &As..."));
    QAction *saveAllAction = new QAction(tr("Save All"));
    QAction *closeAction = new QAction(tr("&Close"));
    QAction *exitAction = new QAction(tr("E&xit"));

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveAction, &QAction::triggered, tabControl, &FileTabControl::save);
    connect(saveAllAction, &QAction::triggered, tabControl, &FileTabControl::saveAll);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);
    connect(closeAction, &QAction::triggered, tabControl, &FileTabControl::closeFile);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // attach close/save/saveall to tabcontrol to set their enabled state
    connect(tabControl, SIGNAL(fileStatusChanged(bool)), saveAction, SLOT(setEnabled(bool)));
    connect(tabControl, SIGNAL(fileStatusChanged(bool)), closeAction, SLOT(setEnabled(bool)));
    connect(tabControl, SIGNAL(fileStatusChanged(bool)), saveAsAction, SLOT(setEnabled(bool)));
    connect(tabControl, SIGNAL(fileStatusChanged(bool)), saveAllAction, SLOT(setEnabled(bool)));

    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(saveAllAction);
    fileMenu->addAction(closeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    closeAction->setEnabled(false);
    saveAction->setEnabled(false);
    saveAsAction->setEnabled(false);
    saveAllAction->setEnabled(false);
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
    tabControl->openFile(filename);
}

void MainWindow::saveAs()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), filename, tr("Flight Plan Files (*.tsv)"));
    if (filename.isEmpty()) {
        return;
    }

    tabControl->saveAs(filename);
}

void MainWindow::initializeTabControl() {
    tabControl = new FileTabControl(this);

    connect(tabControl, SIGNAL(messageGenerated(QString)), statusBar(), SLOT(showMessage(QString)));

    setCentralWidget(tabControl);
}


