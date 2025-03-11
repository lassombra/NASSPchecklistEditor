#include "acdhandler.h"
#include <qboxlayout.h>
#include <qdir.h>

ACDHandler::ACDHandler(QWidget *parent)
    : QTabWidget{parent}
{
    mainTable = new EditTable("", {});
    mainTable->setSecured(true);
    addTab(mainTable, "Groups");
    setTabVisible(0, false);
}

void ACDHandler::load(QString filename) {
    QList<QStringList> data = parseFile(filename);
    if (data.empty()) {
        return;
    }
    if (mainTable->filename().isEmpty()) {
        setTabVisible(0, true);
        emit fileLoadedChanged(true);
    }
    mainTable->setFilename(filename);
    mainTable->setFullData(data);

}

void ACDHandler::save() {
    if(!mainTable->filename().isEmpty()) {
        QFile file(mainTable->filename());
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            emit statusMessage("Could not open " + mainTable->filename() + " to save");
        }
        QTextStream output(&file);
        QList<QStringList> rows = mainTable->fullData();
        for(int i = 0; i < rows.count(); i ++) {
            output << rows[i].join("\t");
        }
        output.flush();
        file.close();
        emit statusMessage("Saved " + mainTable->filename());
    }
}

void ACDHandler::close() {
    if (!mainTable->filename().isEmpty()) {
        mainTable->setFilename("");
        mainTable->setFullData({});
        setTabVisible(0, false);
        emit fileLoadedChanged(false);
    }
}

QList<QStringList> ACDHandler::parseFile(QString filename) {
    QList<QStringList> rows = {};
    QFile file(filename);
    if (!file.exists()) {
        emit statusMessage(filename + " Not Found");
        return rows;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit statusMessage("Could not open " + filename);
        return rows;
    }
    QTextStream input(&file);
    while(!input.atEnd()) {
        QString line = input.readLine();
        rows << line.split("\t");
    }
    file.close();
    return rows;
}
