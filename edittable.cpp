#include "edittable.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>

const QStringList checklistHeaders = {"Text", "Time", "Relative Event", "Panel", "Heading 1", "Heading 2", "LF", "Info", "Item", "Position", "Automatic", "Call Group", "Fail Group", "Remarks"};

EditTable::EditTable(QString filename, const QList<QStringList> *data, QWidget *parent)
    : QTableWidget{parent}
{
    this->m_filename = filename;
    setFullData(data);
    m_secured = false;
}

void EditTable::setFullData(const QList<QStringList> *data) {
    if (!data) {
        setRowCount(0);
        return;
    }
    int rowCount = data->size();
    int columnCount = 14;

    setRowCount(rowCount+1);
    setColumnCount(columnCount);
    setHorizontalHeaderLabels(checklistHeaders);
    for (int row = 0; row < rowCount; row++) {
        for (int column = 0; column < columnCount; column++){
            QStringList actualRow = data->data()[row];
            if (column < actualRow.size()) {
                setItem(row, column, new QTableWidgetItem(actualRow[column]));
            } else {
                setItem(row, column, new QTableWidgetItem(""));
            }
        }
    }
    for(int column = 0; column < columnCount; column++){
        setItem(rowCount, column, new QTableWidgetItem(""));
    }
    if (m_secured) {
        setColumnHidden(columnCount - 1, true);
    }
}

const QString EditTable::filename()
{
    return m_filename;
}

void EditTable::setFilename(QString filename)
{
    if (m_filename != filename) {
        m_filename = filename;
        emit filenameChanged(filename);
    }
}

const QList<QStringList> EditTable::fullData() {
    QList<QStringList> rows = {};
    for(int row = 0; row < rowCount(); row++) {
        QStringList columns = {};
        for (int col = 0; col < columnCount(); col++) {
            columns << item(row, col)->text();
        }
        rows << columns;
    }
    bool found = false;
    while (!found && !rows.isEmpty()) {
        QStringList row = rows.last();
        for (int col = 0; col < row.count(); col++) {
            if (!row[col].isEmpty()) {
                found = true;
                break;
            }
        }
        if (!found) {
            rows.removeLast();
        }
    }
    return rows;
}

void EditTable::setSecured(bool secured) {
    if (m_secured != secured) {
        m_secured = secured;
        setColumnHidden(columnCount() - 1, secured);
        emit securedChanged(secured);
    }
}

const bool EditTable::secured() {
    return m_secured;
}
