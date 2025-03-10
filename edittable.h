#ifndef EDITTABLE_H
#define EDITTABLE_H

#include <QWidget>
#include <QTableWidget>

class EditTable : public QTableWidget
{
    Q_OBJECT
    Q_PROPERTY(bool secured READ secured WRITE setSecured NOTIFY securedChanged FINAL)
public:
    explicit EditTable(QString filename, QWidget *parent = nullptr);
    virtual void loadData(QStringList& rows);
    virtual void save();
    void saveAs(QString filename);
    const bool secured();
    void setSecured(bool secured);

protected:
    QString filename;
private:
    bool m_secured;
signals:
    void messageGenerated(QString message);
    void securedChanged(bool secured);
};

#endif // EDITTABLE_H
