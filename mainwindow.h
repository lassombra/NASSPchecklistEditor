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
    void openFile();
    void saveFile();
    void closeFile();

signals:
};

void writeStatusText(QString);

#endif // MAINWINDOW_H
