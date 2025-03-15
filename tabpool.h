#ifndef TABPOOL_H
#define TABPOOL_H

#include <QObject>
#include "editortab.h"

///
/// \brief The TabPool class
/// This class exists to simplify loading and closing to avoid having to fully
/// destroy and recreate UI objects every time.  Instead, the UI
/// objects are owned by this class.  They'll get cleaned up when this class gets cleaned up
/// (such as on application close) but otherwise they can be purged and reused.
///
class TabPool : public QWidget
{
    Q_OBJECT
public:
    explicit TabPool(QWidget *parent = nullptr);
    EditorTab* getTab();
    void releaseAllTabs();
private:
    QList<EditorTab*> tabs;
    int currentIndex = 0;
signals:
};

#endif // TABPOOL_H
