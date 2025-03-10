#ifndef ACDEDITTABLE_H
#define ACDEDITTABLE_H

#include "edittable.h"
#include <QWidget>

class ACDEditTable : public EditTable
{
public:
    explicit ACDEditTable(QString filename, QWidget* widget = nullptr);
    virtual void loadData(QStringList& rows);
    virtual void save();
};

#endif // ACDEDITTABLE_H
