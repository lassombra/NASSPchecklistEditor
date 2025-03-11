#include "edittable.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>

EditTable::EditTable(QString filename, const QList<QStringList> *data, QWidget *parent)
    : QTableWidget{parent}
{
    this->m_filename = filename;
    setFullData(data);
    m_secured = false;
}

QStringList generateHeaders(int count) {
    QStringList headers;
    for(int i = 0; i < count; i++) {
        int quotient = i;
        QString header;
        do {
            header.prepend(QChar('A'+quotient % 26));
            quotient = quotient / 26 - 1;
        } while (quotient >= 0);
        headers << header;
    }
    return headers;
}

void EditTable::setFullData(const QList<QStringList> *data) {
    if (!data) {
        setRowCount(0);
        return;
    }
    int rowCount = data->size();
    int columnCount = data->first().size();

    setRowCount(rowCount+1);
    setColumnCount(columnCount);
    setHorizontalHeaderLabels(generateHeaders(columnCount));
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
    while (!found) {
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
