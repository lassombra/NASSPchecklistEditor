#ifndef EDITORTAB_H
#define EDITORTAB_H

#include "edittable.h"
#include <QWidget>
#include <QBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <qdir.h>

class EditorTab : public QWidget
{
    Q_OBJECT
public:
    explicit EditorTab(QWidget *parent = nullptr);
    void populate(const QStringList& metadata, const QString& actualFilename, const QList<QStringList> &data);
    const QStringList getMetadata(const QDir &rootDirectory);
    const QList<QStringList> getData();
private:
    EditTable* table;
    void addCheckboxes(QBoxLayout& mainLayout);
    void addForm(QBoxLayout& mainLayout);
    QCheckBox *chkAutomatic, *chkManual, *chkEssential, *chkSlow;
    QLineEdit *txtName, *txtHeading, *txtTime, *txtDeadline, *txtRelativeEvent, *txtSound;
signals:
    void nameChanged(const QString& newName);
};

#endif // EDITORTAB_H
