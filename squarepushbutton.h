#ifndef SQUAREPUSHBUTTON_H
#define SQUAREPUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QWidget>

class SquarePushButton : public QPushButton
{
public:
    explicit SquarePushButton(QWidget *parent = nullptr);
    explicit SquarePushButton(const QString &text, QWidget *parent = nullptr);
    SquarePushButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);
    ~SquarePushButton();

    QSize sizeHint() const override;
};

#endif // SQUAREPUSHBUTTON_H
