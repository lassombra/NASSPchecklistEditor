#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void createTable();
    void openFile();

    QTableWidget *tableView;

signals:
};

#endif // MAINWINDOW_H
