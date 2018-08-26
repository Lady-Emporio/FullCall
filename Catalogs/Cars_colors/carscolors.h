#ifndef CARSCOLORS_H
#define CARSCOLORS_H

#include "allinclude.h"
#include "Settings/settings.h"
#include "Catalogs/BaseTable/basetable.h"
class CarsColors : public BaseTable
{
    Q_OBJECT
public:
    explicit CarsColors(QWidget *parent = 0);
};

#endif // CARSCOLORS_H
