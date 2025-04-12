#include "squarepushbutton.h"



SquarePushButton::SquarePushButton(QWidget *parent) : QPushButton(parent)
{

}

SquarePushButton::SquarePushButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{

}

SquarePushButton::SquarePushButton(const QIcon &icon, const QString &text, QWidget *parent) : QPushButton(icon, text, parent)
{

}

SquarePushButton::~SquarePushButton()
{

}

QSize SquarePushButton::sizeHint() const
{
    QFontMetrics metrics(this->font());
    auto width = metrics.horizontalAdvance(this->text());
    auto height = metrics.height();
    return QSize(width + 8, height + 8);
}
