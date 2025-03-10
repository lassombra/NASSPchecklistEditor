#include "edittable.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>

EditTable::EditTable(QString filename, QWidget *parent)
    : QWidget{parent}
{
    this->filename = filename;
    createEmptyTable();
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

void EditTable::loadData(QStringList& data) {
    int rowCount = data.size();
    int columnCount = data.first().split("\t").size();

    tableView->setRowCount(rowCount+1);
    tableView->setColumnCount(columnCount);
    tableView->setHorizontalHeaderLabels(generateHeaders(columnCount));
    for (int row = 0; row < rowCount; row++) {
        QStringList columns = data[row].split("\t");
        for (int column = 0; column < columnCount; column++){
            if (column < columns.size()) {
                tableView->setItem(row, column, new QTableWidgetItem(columns[column]));
            } else {
                tableView->setItem(row, column, new QTableWidgetItem(""));
            }
        }
    }
    for(int column = 0; column < columnCount; column++){
        tableView->setItem(rowCount, column, new QTableWidgetItem(""));
    }
}

void EditTable::createEmptyTable() {
    tableView = new QTableWidget(this);
    QLayout* layout = new QVBoxLayout();
    layout->addWidget(tableView);
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);
    this->setContentsMargins(0,0,0,0);
    this->setStyleSheet("EditTable {border: none; }");
}

void EditTable::save() {
    saveAs(filename);
}

void EditTable::saveAs(QString filename) {
    QFile file(filename);
    emit messageGenerated("Saving file " + filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QList<QStringList> rows = {};
    for(int row = 0; row < tableView->rowCount(); row++) {
        QStringList columns = {};
        for (int col = 0; col < tableView->columnCount(); col++) {
            columns << tableView->item(row, col)->text();
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
    QTextStream stream(&file);
    for(int row = 0; row < rows.count(); row++) {
        stream << rows[row].join("\t");
        if (row < rows.count() - 1) {
            stream << "\n";
        }
    }
    stream.flush();
    file.close();
    emit messageGenerated("Saved " + filename);
}
