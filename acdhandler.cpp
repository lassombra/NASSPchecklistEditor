#include "acdhandler.h"
#include <qboxlayout.h>
#include <qdir.h>

ACDHandler::ACDHandler(QWidget *parent)
    : QWidget{parent}
{
    this->setLayout(new QVBoxLayout(this));
    tabControl = new FileTabControl(this);
    this->layout()->addWidget(tabControl);
    this->layout()->setContentsMargins(0,0,0,0);
    this->setContentsMargins(0,0,0,0);
}

void ACDHandler::load(QString filename) {
    QList<QStringList> data = parseFile(filename);
    if (data.empty()) {
        return;
    }

}

void ACDHandler::save() {

}

void ACDHandler::close() {

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
