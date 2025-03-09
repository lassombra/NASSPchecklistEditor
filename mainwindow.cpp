#include "mainwindow.h"
#include <QMenuBar>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    createMenus();
    createStatusBar();
    createTable();
}

void MainWindow::createMenus() {

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *openAction = new QAction(tr("&Open"));
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(openAction);
    QAction *exitAction = new QAction(tr("E&xit"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);
}

void MainWindow::createStatusBar() {
    statusBar();
}

void MainWindow::createTable() {
    tableView = new QTableWidget(this);
    tableView->setColumnCount(4);
    tableView->setRowCount(500);
    QStringList headers = {"A", "B", "C", "D"};
    tableView->setHorizontalHeaderLabels(headers);
    setCentralWidget(tableView);
}

QStringList generateHeaders(int count) {
    QStringList headers;
    for(int i = 0; i < count; i++) {
        int quotient = i;
        QString header;
        do {
            header.prepend(QChar('A'+quotient % 26));
            quotient = quotient / 26 - 1;
        } while (quotient >= 0);
        headers << header;
    }
    return headers;
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

    int rowCount = lines.size();
    int columnCount = lines.first().split("\t").size();

    tableView->setRowCount(rowCount+1);
    tableView->setColumnCount(columnCount);
    tableView->setHorizontalHeaderLabels(generateHeaders(columnCount));
    for (int row = 0; row < rowCount; row++) {
        QStringList columns = lines[row].split("\t");
        for (int column = 0; column < columns.size(); column++){
            tableView->setItem(row, column, new QTableWidgetItem(columns[column]));
        }
    }
}
