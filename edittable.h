#ifndef EDITTABLE_H
#define EDITTABLE_H

#include <QWidget>
#include <QTableWidget>

class EditTable : public QTableWidget
{
    Q_OBJECT
    Q_PROPERTY(bool secured READ secured WRITE setSecured NOTIFY securedChanged FINAL)
    Q_PROPERTY(QList<QStringList> fullData READ fullData WRITE setFullData NOTIFY fullDataChanged FINAL)
public:
    explicit EditTable(QString filename, QList<QStringList> data, QWidget *parent = nullptr);
    void save();
    void saveAs(QString filename);
    const bool secured();
    void setSecured(bool secured);
    const QList<QStringList> fullData();
    void setFullData(QList<QStringList> newData);

protected:
    QString filename;
private:
    bool m_secured;
signals:
    void messageGenerated(QString message);
    void securedChanged(bool secured);
    void fullDataChanged(QList<QStringList> data);
};

#endif // EDITTABLE_H
