#ifndef ACDHANDLER_H
#define ACDHANDLER_H

#include <QWidget>
#include "filetabcontrol.h"

class ACDHandler : public QWidget
{
    Q_OBJECT
public:
    explicit ACDHandler(QWidget *parent = nullptr);
public slots:
    // void load(QString filename);
    // void save();
    // void close();
private:
    FileTabControl* tabControl;
signals:
    void statusMessage(QString message);
    void fileLoadedChanged(bool loaded);
};

#endif // ACDHANDLER_H
