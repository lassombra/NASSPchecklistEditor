#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "acdhandler.h"
#include <QMainWindow>
#include <QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void createMenus();
    void createStatusBar();
    void initializeTabControl();
    void openFile();
    void saveAs();
private:
    ACDHandler* tabControl;

signals:
};

#endif // MAINWINDOW_H
