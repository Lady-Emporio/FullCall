#ifndef BASETABLE_H
#define BASETABLE_H

#include "allinclude.h"
#include "Settings/settings.h"
class BaseTable : public QWidget
{
    Q_OBJECT

public:
    void makeGui();
    QSqlTableModel *modelTable;
    QSqlRelationalTableModel *modelRelational;

    QLineEdit *filter;
    explicit BaseTable(QWidget *parent = 0);
public slots:
    void action_addRow();
    void action_refreshModel();
    void action_commitModel();
    void action_filter();
};

#endif // BASETABLE_H
