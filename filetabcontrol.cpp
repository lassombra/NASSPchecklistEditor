#include "edittable.h"
#include "filetabcontrol.h"
#include <QVBoxLayout>
#include <qdir.h>

FileTabControl::FileTabControl(QWidget *parent)
    : QWidget{parent}
{
    tabControl = new QTabWidget(this);
    this->setLayout(new QVBoxLayout(this));
    this->setContentsMargins(0,0,0,0);
    this->layout()->setContentsMargins(0,0,0,0);
    this->layout()->addWidget(tabControl);
}

void FileTabControl::openFile(QString filename) {
    bool firstFile = tabControl->count() == 0;
    QFile file(filename);
    if (!file.open(QIODeviceBase::ReadOnly | QIODeviceBase::Text)) {
        emit messageGenerated("Could not open file " + filename);
        return;
    }
    QTextStream stream(&file);
    QStringList rows = {};
    while (!stream.atEnd()) {
        rows << stream.readLine();
    }
    EditTable* table = new EditTable(filename);
    table->setSecured(true);
    table->loadData(rows);
    connect(table, &EditTable::messageGenerated, this, &FileTabControl::messageGenerated);
    tabControl->addTab(table, "Tab");
    if (firstFile) {
        emit fileStatusChanged(true);
    }
}

void FileTabControl::closeFile() {
    if (tabControl->count() > 0) {
        EditTable* table = (EditTable*)tabControl->currentWidget();
        tabControl->removeTab(tabControl->currentIndex());
        table->deleteLater();
        if (tabControl->count() == 0) {
            emit fileStatusChanged(false);
        }
    }
}

void FileTabControl::save() {
    if (tabControl->count() > 0) {
        EditTable* table = (EditTable*)tabControl->currentWidget();
        table->save();
    }
}

void FileTabControl::closeAll() {
    while(tabControl->count() > 0) {
        QWidget* tab = tabControl->widget(0);
        tabControl->removeTab(0);
        tab->deleteLater();
    }
    emit fileStatusChanged(false);
}
