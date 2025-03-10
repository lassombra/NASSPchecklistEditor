#ifndef FILETABCONTROL_H
#define FILETABCONTROL_H

#include <QWidget>
#include <QTabWidget>

class FileTabControl : public QWidget
{
    Q_OBJECT
public:
    explicit FileTabControl(QWidget *parent = nullptr);
    void openFile(QString filename);
    void closeFile();
    void save();
    void saveAs(QString filename);
    void saveAll();
    void closeAll();

private:
    QTabWidget* tabControl;

signals:
    void messageGenerated(QString message);
    void fileStatusChanged(bool anyOpen);
};

#endif // FILETABCONTROL_H
