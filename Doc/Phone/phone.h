#ifndef PHONE_H
#define PHONE_H

#include "allinclude.h"
#include "Settings/settings.h"
#include "Catalogs/BaseTable/basetable.h"
class Phone : public QWidget
{
    Q_OBJECT
    void makeGui();
    int orderParent;
    QComboBox * f_statuRec;
    QLabel *idRec;
    QString id;
public:
    explicit Phone(QWidget *parent = 0, int orderParent=0);
signals:

public slots:
    void action_refreshAll();
};

#endif // PHONE_H
