#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "filetabcontrol.h"

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
private:
    FileTabControl* tabControl;

signals:
};

#endif // MAINWINDOW_H
