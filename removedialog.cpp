#include "removedialog.h"
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>
#include <qboxlayout.h>

RemoveDialog::RemoveDialog(QWidget *parent)
    : QDialog(parent)
{
    auto txt = new QLabel(this);
    txt->setText("Delete file from file system or simply detach it (to be attached again later or to another master file?");
    this->setLayout(new QVBoxLayout(this));
    this->layout()->addWidget(txt);
    this->setSizeGripEnabled(false);
    this->setModal(true);
    this->addButtons();
    m_decision = InvalidDecision;
}

RemoveDialog::~RemoveDialog()
{
}

int RemoveDialog::decision()
{
    return m_decision;
}

void RemoveDialog::addButtons()
{
    auto buttons = new QDialogButtonBox(this);

    buttons->addButton("Cancel", QDialogButtonBox::RejectRole);
    auto btnDelete = buttons->addButton("Delete", QDialogButtonBox::ActionRole);
    auto btnDetach = buttons->addButton("Detach", QDialogButtonBox::ActionRole);

    connect(btnDelete, &QPushButton::clicked, this, [this](bool checked){setDecision(DeleteAction);});
    connect(btnDetach, &QPushButton::clicked, this, [this](bool checked){setDecision(DetachAction);});
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout()->addWidget(buttons);
}

void RemoveDialog::setDecision(int decision)
{
    m_decision = decision;
    emit decisionChanged(m_decision);
    accept();
}
