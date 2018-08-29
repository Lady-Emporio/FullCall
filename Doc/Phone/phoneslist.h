#ifndef PHONESLIST_H
#define PHONESLIST_H

#include "allinclude.h"
#include "Settings/settings.h"
#include "Catalogs/BaseTable/basetable.h"

class PhonesList : public BaseTable
{
    Q_OBJECT
public:
    int orderParent;
    explicit PhonesList(QWidget *parent = 0,int orderParent=0);

signals:

public slots:
    void action_addRow();
};

#endif // PHONESLIST_H
