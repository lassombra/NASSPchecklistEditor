#ifndef EDITTABLE_H
#define EDITTABLE_H

#include <QWidget>
#include <QTableWidget>

class EditTable : public QWidget
{
    Q_OBJECT
public:
    explicit EditTable(QString filename, QWidget *parent = nullptr);
    void loadData(QStringList& rows);
    void save();
    void saveAs(QString filename);
private:
    void createEmptyTable();
    QString filename;
    QTableWidget* tableView;

signals:
    void messageGenerated(QString message);
};

#endif // EDITTABLE_H
