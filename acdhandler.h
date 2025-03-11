#ifndef ACDHANDLER_H
#define ACDHANDLER_H

#include <QWidget>
#include "edittable.h"

class ACDHandler : public QTabWidget
{
    Q_OBJECT
public:
    explicit ACDHandler(QWidget *parent = nullptr);
public slots:
    void load(QString filename);
    void save();
    void close();
private:
    void loadChecklist(QString filename, QList<QStringList> data);
    void loadAllChecklists(QList<QStringList> &groups);
    QList<QStringList> parseFile(QString filename);

    QList<EditTable*> checklists;
    EditTable* mainTable;
signals:
    void statusMessage(QString message);
    void fileLoadedChanged(bool loaded);
};

#endif // ACDHANDLER_H
