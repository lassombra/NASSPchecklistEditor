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
    void loadChecklist(QString name, QString filename, const QList<QStringList> &data);
    void loadAllChecklists(const QList<QStringList> &groups, QString rootFilename);
    void saveData(QString filename, const QList<QStringList> &data);
    QList<QStringList> parseFile(QString filename);

    QList<EditTable*> checklists;
    EditTable* mainTable;
signals:
    void statusMessage(QString message, int timeout = 0);
    void fileLoadedChanged(bool loaded);
};

#endif // ACDHANDLER_H
