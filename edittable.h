#ifndef EDITTABLE_H
#define EDITTABLE_H

#include <QWidget>
#include <QTableWidget>

class EditTable : public QTableWidget
{
    Q_OBJECT
    Q_PROPERTY(bool secured READ secured WRITE setSecured NOTIFY securedChanged FINAL)
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged FINAL)
public:
    explicit EditTable(QString filename, const QList<QStringList> *data, QWidget *parent = nullptr);
    const bool secured();
    void setSecured(bool secured);
    const QList<QStringList> fullData();
    void setFullData(const QList<QStringList> *newData);
    const QString filename();
    void setFilename(QString filename);
private:
    QString m_filename;
    bool m_secured;
signals:
    void messageGenerated(QString message);
    void securedChanged(bool secured);
    void filenameChanged(QString filename);
};

#endif // EDITTABLE_H
