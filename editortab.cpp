#include "editortab.h"
#include <QFormLayout>

// HELPER FUNCTIONS
QString boolToString(const bool &value) {
    if(value) {
        return "1";
    } else {
        return "0";
    }
}

bool stringToBool(const QString &value) {
    if (value == "1") {
        return true;
    } else {
        return false;
    }
}


// Main Class

EditorTab::EditorTab(QWidget *parent)
    : QWidget{parent}
{
    QBoxLayout* mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    addForm(*mainLayout);
    addCheckboxes(*mainLayout);
    table = new EditTable("", nullptr);
    mainLayout->addWidget(table);
}

void EditorTab::populate(const QStringList &metadata, const QString &actualFilename, const QList<QStringList> &data)
{
    txtName->setText(metadata[0]);
    txtTime->setText(metadata[1]);
    txtDeadline->setText(metadata[2]);
    txtRelativeEvent->setText(metadata[3]);
    txtHeading->setText(metadata[4]);
    chkAutomatic->setChecked(stringToBool(metadata[5]));
    chkManual->setChecked(stringToBool(metadata[6]));
    chkEssential->setChecked(stringToBool(metadata[7]));
    txtSound->setText(metadata[8]);
    chkSlow->setChecked(stringToBool(metadata[9]));
    table->setFilename(actualFilename);
    table->setFullData(&data);
}

const QStringList EditorTab::getMetadata(const QDir &rootDirectory)
{
    QStringList metadata = {};
    metadata << txtName->text();
    metadata << txtTime->text();
    metadata << txtDeadline->text();
    metadata << txtRelativeEvent->text();
    metadata << txtHeading->text();
    metadata << boolToString(chkAutomatic->isChecked());
    metadata << boolToString(chkManual->isChecked());
    metadata << boolToString(chkEssential->isChecked());
    metadata << txtSound->text();
    metadata << boolToString(chkSlow->isChecked());
    metadata << rootDirectory.relativeFilePath(table->filename());
    return metadata;
}

const QList<QStringList> EditorTab::getData()
{
    return table->fullData();
}

void EditorTab::addCheckboxes(QBoxLayout &mainLayout)
{
    QLayout* checkboxes = new QHBoxLayout();
    mainLayout.addLayout(checkboxes);
    chkAutomatic = new QCheckBox();
    chkManual = new QCheckBox();
    chkEssential = new QCheckBox();
    chkSlow = new QCheckBox();

    chkAutomatic->setText("Automatic");
    chkManual->setText("Manual");
    chkEssential->setText("Essential");
    chkSlow->setText("Slow");

    checkboxes->addWidget(chkAutomatic);
    checkboxes->addWidget(chkManual);
    checkboxes->addWidget(chkEssential);
    checkboxes->addWidget(chkSlow);
}

void EditorTab::addForm(QBoxLayout &mainLayout)
{
    QFormLayout* form = new QFormLayout();
    mainLayout.addLayout(form);

    txtName = new QLineEdit();
    txtHeading = new QLineEdit();
    txtTime = new QLineEdit();
    txtDeadline = new QLineEdit();
    txtRelativeEvent = new QLineEdit();
    txtSound = new QLineEdit();

    connect(txtName, &QLineEdit::textEdited, this, &EditorTab::nameChanged);

    form->addRow("Name", txtName);
    form->addRow("Heading", txtHeading);
    form->addRow("Time", txtTime);
    form->addRow("Deadline", txtDeadline);
    form->addRow("RelativeEvent", txtRelativeEvent);
    form->addRow("Sound", txtSound);
}

