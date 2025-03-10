#ifndef EDITTABLE_H
#define EDITTABLE_H

#include <QWidget>
#include <QTableWidget>

class EditTable : public QWidget
{
    Q_OBJECT
public:
    explicit EditTable(QString filename, QWidget *parent = nullptr);
    virtual void loadData(QStringList& rows);
    virtual void save();
    void saveAs(QString filename);
protected:
    void createEmptyTable();
    QString filename;
    QTableWidget* tableView;

signals:
    void messageGenerated(QString message);
};

#endif // EDITTABLE_H
