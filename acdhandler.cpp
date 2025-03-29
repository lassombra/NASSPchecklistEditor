#include "acdhandler.h"
#include <qboxlayout.h>
#include <qcoreapplication.h>
#include <qdir.h>

const QStringList groupHeaders = {"Name", "Time", "Deadline", "Relative Event", "Heading", "Automatic", "Manual", "Essential", "Sound", "Slow", "File"};
const QStringList checklistHeaders = {"Text", "Time", "Relative Event", "Panel", "Heading 1", "Heading 2", "LF", "Info", "Item", "Position", "Automatic", "Call Group", "Fail Group", "Remarks"};

ACDHandler::ACDHandler(QWidget *parent)
    : QTabWidget{parent}
{
    currentFile = nullptr;
    this->setTabsClosable(true);
    connect(this, &QTabWidget::tabCloseRequested, this, &ACDHandler::initRemoveTab);
    tabPool = new TabPool(this);
}

void ACDHandler::load(QString filename) {
    if (currentFile) {
        close();
    }
    currentFile = new QFileInfo(filename);
    QList<QStringList> data = parseFile(filename);
    if (data.empty()) {
        return;
        delete currentFile;
        currentFile = nullptr;
    }
    emit fileLoadedChanged(true);
    loadAllChecklists(data);
    emit statusMessage("Loaded", 5000);
}

void ACDHandler::save() {
    if(currentFile) {
        QDir directory = currentFile->absoluteDir();
        QList<QStringList> metadata = {};
        for (int i = 0; i < count(); i++) {
            auto tab = (EditorTab*)widget(i);
            metadata << saveData(tab->getMetadata(directory), tab->getData());
        }
        saveData(currentFile->absoluteFilePath(), groupHeaders, metadata);
    }
}


void ACDHandler::saveData(QString filename, const QStringList &headers, const QList<QStringList> &data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        emit statusMessage("Could not open " + filename + " to save");
    }
    QCoreApplication::processEvents();
    QTextStream output(&file);
    QStringList outdata = {};
    outdata<< headers.join("\t");
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
    if (currentFile) {
        clear();
        delete currentFile;
        currentFile = nullptr;
        QCoreApplication::processEvents();
        tabPool->releaseAllTabs();
        emit fileLoadedChanged(false);
    }
}

void ACDHandler::loadChecklist(QStringList metadata, QString filename, const QList<QStringList> &data)
{
    EditorTab *tab = tabPool->getTab();
    tab->populate(metadata, filename, data);
    auto id = addTab(tab, metadata[0]);
    connect(tab, &EditorTab::nameChanged, this, [id, this](QString newName){this->setTabText(id, newName);});
    QCoreApplication::processEvents();
}

void ACDHandler::loadAllChecklists(const QList<QStringList> &groups)
{
    QDir rootDir = currentFile->absoluteDir();
    for(int row = 0; row < groups.count(); row++) {
        QStringList group = groups[row];
        if (!group[0].isEmpty() && !group[group.count()-1].isEmpty()) {
            QString fullPath = rootDir.filePath(group[group.count() - 1]);
            QList<QStringList> data = parseFile(fullPath);
            if (!data.isEmpty()) {
                loadChecklist(group, fullPath, data);
            }
        }
    }
}

QStringList ACDHandler::saveData(QStringList metadata, const QList<QStringList> &data)
{
    saveData(currentFile->absoluteDir().absoluteFilePath(metadata[10]), checklistHeaders, data);
    return metadata;
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
    rows.removeFirst();
    emit statusMessage("Loaded " + filename);
    return rows;
}

void ACDHandler::initRemoveTab(int index)
{
    m_pendingRemoveIndex = index;
    removeDialog = new RemoveDialog(this);
    connect(removeDialog, &RemoveDialog::decisionChanged, this, &ACDHandler::acceptRemove);
    connect(removeDialog, &RemoveDialog::rejected, this, &ACDHandler::cancelRemove);
    removeDialog->show();
}

void ACDHandler::cancelRemove()
{
    removeDialog->deleteLater();
    removeDialog = nullptr;
}

void ACDHandler::acceptRemove(int decision)
{
    auto tab = (EditorTab *)this->widget(m_pendingRemoveIndex);
    this->removeTab(m_pendingRemoveIndex);
    if (decision == RemoveDialog::DeleteAction) {
        QFile file(tab->filePath());
        file.remove();
        save();
    }
}
