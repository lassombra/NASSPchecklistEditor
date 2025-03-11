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
    QAction *closeAction = new QAction(tr("&Close"));
    QAction *exitAction = new QAction(tr("E&xit"));

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveAction, &QAction::triggered, tabControl, &ACDHandler::save);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);
    connect(closeAction, &QAction::triggered, tabControl, &ACDHandler::close);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // attach close/save/saveall to tabcontrol to set their enabled state
    connect(tabControl, &ACDHandler::fileLoadedChanged, saveAction, &QAction::setEnabled);
    connect(tabControl, &ACDHandler::fileLoadedChanged, closeAction, &QAction::setEnabled);
    connect(tabControl, &ACDHandler::fileLoadedChanged, saveAsAction, &QAction::setEnabled);

    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(closeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    closeAction->setEnabled(false);
    saveAction->setEnabled(false);
    saveAsAction->setEnabled(false);
}

void MainWindow::createStatusBar() {
    statusBar();
}


void MainWindow::openFile() {
    QString filename = QFileDialog::getOpenFileName(this, tr("select file"), "", tr("Apollo Checklist Definition (*.acd)"));
    if (filename.isEmpty()) {
        // user canceled open file
        return;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    tabControl->load(filename);
}

void MainWindow::saveAs()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), filename, tr("Apollo Checklist Definition (*.acd)"));
    if (filename.isEmpty()) {
        return;
    }

    // tabControl->saveAs(filename);
}

void MainWindow::initializeTabControl() {
    tabControl = new ACDHandler(this);

    connect(tabControl, SIGNAL(messageGenerated(QString)), statusBar(), SLOT(showMessage(QString)));

    setCentralWidget(tabControl);
}


