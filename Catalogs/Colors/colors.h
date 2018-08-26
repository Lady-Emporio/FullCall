#ifndef COLORS_H
#define COLORS_H

#include "allinclude.h"
#include "Settings/settings.h"
class Colors : public QWidget
{
    Q_OBJECT
    QSqlTableModel *model;
    QLineEdit *filter;
    void makeGui();
public:
    explicit Colors(QWidget *parent = 0);
public slots:
    void action_addRow();
    void action_refreshModel();
    void action_commitModel();
    void action_filter();
};

#endif // COLORS_H
