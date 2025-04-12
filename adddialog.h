#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

class AddDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(int decision READ decision WRITE setDecision NOTIFY decisionChanged FINAL)

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();
    int decision();

    enum AddAction{
        InvalidDecision = -1,
        Attach,
        Copy,
        New
    };

private:
    void addButtons();
    void setDecision(int decision);
    int m_decision;

signals:
    void decisionChanged(int decision);
};

#endif // ADDDIALOG_H
