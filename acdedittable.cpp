#include "acdedittable.h"

ACDEditTable::ACDEditTable(QString filename, QWidget* widget) : EditTable(filename, widget) {}

void ACDEditTable::loadData(QStringList& rows) {
    EditTable::loadData(rows);
    tableView->hideColumn(tableView->columnCount() - 1);
}

void ACDEditTable::save() {
    EditTable::save();
}
