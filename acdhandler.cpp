#include "acdhandler.h"
#include <qboxlayout.h>
#include <qcoreapplication.h>
#include <qdir.h>

ACDHandler::ACDHandler(QWidget *parent)
    : QTabWidget{parent}
{
    mainTable = new EditTable("", nullptr);
    mainTable->setSecured(true);
    addTab(mainTable, "Groups");
    setTabVisible(0, false);
}

void ACDHandler::load(QString filename) {
    if (!mainTable->filename().isEmpty()) {
        close();
    }
    QList<QStringList> data = parseFile(filename);
    if (data.empty()) {
        return;
    }
    setTabVisible(0, true);
    emit fileLoadedChanged(true);
    mainTable->setFilename(filename);
    mainTable->setFullData(&data);
    loadAllChecklists(data, filename);
    emit statusMessage("Loaded", 5000);
}

void ACDHandler::save() {
    if(!mainTable->filename().isEmpty()) {
        saveData(mainTable->filename(), mainTable->fullData());
        for (EditTable* table : checklists) {
            saveData(table->filename(), table->fullData());
        }
    }
}


void ACDHandler::saveData(QString filename, const QList<QStringList> &data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        emit statusMessage("Could not open " + filename + " to save");
    }
    QCoreApplication::processEvents();
    QTextStream output(&file);
    QStringList outdata = {};
    for(int i = 0; i < data.count(); i ++) {
        outdata << data[i].join("\t");
    }
    output << outdata.join("\n");
    output.flush();
    file.close();
    emit statusMessage("Saved " + filename);
    QCoreApplication::processEvents();
}

void ACDHandler::close() {
    if (!mainTable->filename().isEmpty()) {
        clear();
        QCoreApplication::processEvents();
        for (EditTable* widget : checklists) {
            delete widget;
            QCoreApplication::processEvents();
        }
        checklists.clear();
        mainTable->setFilename("");
        mainTable->setFullData(nullptr);
        emit fileLoadedChanged(false);
        addTab(mainTable, "Groups");
        setTabVisible(0, false);
    }
}

void ACDHandler::loadChecklist(QString name, QString filename, const QList<QStringList> &data)
{
    EditTable *table = new EditTable(filename, &data);
    checklists << table;
    addTab(table, name);
    QCoreApplication::processEvents();
}

void ACDHandler::loadAllChecklists(const QList<QStringList> &groups, QString rootFilename)
{
    QFileInfo rootFile(rootFilename);
    QDir rootDir = rootFile.absoluteDir();
    for(int row = 0; row < groups.count(); row++) {
        QStringList group = groups[row];
        if (!group[0].isEmpty() && !group[group.count()-1].isEmpty()) {
            QString fullPath = rootDir.filePath(group[group.count() - 1]);
            QList<QStringList> data = parseFile(fullPath);
            if (!data.isEmpty()) {
                loadChecklist(group[0], fullPath, data);
            }
        }
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
    emit statusMessage("Loaded " + filename);
    return rows;
}
