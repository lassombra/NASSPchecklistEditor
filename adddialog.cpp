#include "adddialog.h"
#include <qboxlayout.h>
#include <qdialogbuttonbox.h>
#include <qlabel.h>
#include <qpushbutton.h>



AddDialog::AddDialog(QWidget *parent)
{
    m_decision = InvalidDecision;
    auto txt = new QLabel(this);
    txt->setText("Add a new blank tab or Import an existing one?  Note Import will simply reference the existing file, while Copy will create a new file to hold the contents.");
    this->setLayout(new QVBoxLayout(this));
    this->layout()->addWidget(txt);
    this->setSizeGripEnabled(false);
    this->setModal(true);
    this->addButtons();
}

AddDialog::~AddDialog()
{

}

int AddDialog::decision() {
    return m_decision;
}

void AddDialog::addButtons() {
    auto buttons = new QDialogButtonBox(this);
    buttons->addButton("Cancel", QDialogButtonBox::RejectRole);
    auto btnNew = buttons->addButton("New", QDialogButtonBox::ActionRole);
    auto btnImport = buttons->addButton("Import", QDialogButtonBox::ActionRole);
    auto btnCopy = buttons->addButton("Copy", QDialogButtonBox::ActionRole);

    connect(btnNew, &QPushButton::clicked, this, [this](bool checked){setDecision(New);});
    connect(btnImport, &QPushButton::clicked, this, [this](bool checked){setDecision(Attach);});
    connect(btnCopy, &QPushButton::clicked, this, [this](bool checked){setDecision(Copy);});
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout()->addWidget(buttons);
}

void AddDialog::setDecision(int decision)
{
    m_decision = decision;
    emit decisionChanged(m_decision);
    accept();
}
