#ifndef CARSCHOOSE_H
#define CARSCHOOSE_H

#include "allinclude.h"
#include "Settings/settings.h"
class CarsChoose : public QWidget
{
    Q_OBJECT
    void makeGui();
    QSqlRelationalTableModel *model;
public:
    explicit CarsChoose(QWidget *parent = 0);

signals:

public slots:
};

#endif // CARSCHOOSE_H
