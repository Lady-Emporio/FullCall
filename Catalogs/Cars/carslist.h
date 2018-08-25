#ifndef CARSLIST_H
#define CARSLIST_H

#include "allinclude.h"
#include "Settings/settings.h"
class CarsList : public QWidget
{
    Q_OBJECT
    void makeGui();
    QSqlTableModel *model;
    QLineEdit *filter;
public:
    explicit CarsList(QWidget *parent = 0);

signals:

public slots:
    void action_addRow();
    void action_refreshModel();
    void action_commitModel();
    void action_filter();
};

#endif // CARSLIST_H
