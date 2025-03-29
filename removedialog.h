#ifndef REMOVEDIALOG_H
#define REMOVEDIALOG_H

#include <QDialog>

namespace Ui {
class RemoveDialog;
}

class RemoveDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(int decision READ decision WRITE setDecision NOTIFY decisionChanged FINAL)

public:
    explicit RemoveDialog(QWidget *parent = nullptr);
    ~RemoveDialog();
    int decision();

    enum RemoveAction{
        InvalidDecision = -1,
        DeleteAction,
        DetachAction
    };

private:
    void addButtons();
    void setDecision(int decision);
    int m_decision;

signals:
    void decisionChanged(int decision);
};

#endif // REMOVEDIALOG_H
