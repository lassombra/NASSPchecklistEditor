#ifndef ACDHANDLER_H
#define ACDHANDLER_H

#include <QWidget>
#include "removedialog.h"
#include "tabpool.h"

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
    void loadChecklist(QStringList metadata, QString filename, const QList<QStringList> &data);
    void loadAllChecklists(const QList<QStringList> &groups);
    QStringList saveData(QStringList metadata, const QList<QStringList> &data);
    void saveData(QString filename, const QStringList &headers, const QList<QStringList> &data);
    QList<QStringList> parseFile(QString filename);
    void initRemoveTab(int index);
    void cancelRemove();
    void acceptRemove(int decision);

    QFileInfo* currentFile;
    TabPool* tabPool;
    RemoveDialog* removeDialog;
    int m_pendingRemoveIndex;
signals:
    void statusMessage(QString message, int timeout = 0);
    void fileLoadedChanged(bool loaded);
};

#endif // ACDHANDLER_H
