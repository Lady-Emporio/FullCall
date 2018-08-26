#ifndef BASETABLE_H
#define BASETABLE_H

#include "allinclude.h"
#include "Settings/settings.h"
class BaseTable : public QWidget
{
    Q_OBJECT

public:
    QMenuBar * mainMenu;
    void makeGui();
    QSqlTableModel *modelTable;
    QSqlRelationalTableModel *modelRelational;
    QPushButton * setFilterButton;
    QLineEdit *filter;
    QPushButton * commitButton;
    QTableView *tableView;
    explicit BaseTable(QWidget *parent = 0);
    void hideFilter();
public slots:
    void action_addRow();
    void action_refreshModel();
    void action_commitModel();
    void action_filter();
};
class SubTable : public BaseTable
{
    Q_OBJECT
   int indexColumnDate;
public:
   int indexParent;
   QString parent_code;
    explicit SubTable(QWidget *parent, int indexColumnDate);
public slots:
    void action_addRow();
};

class SubTableOnlyParent : public BaseTable
{
    Q_OBJECT
    int indexParent;
    QString parent_code;
public:
    explicit SubTableOnlyParent(QWidget *parent, int indexParent,QString parent_code);
public slots:
    void action_addRow();
};

class OpenSomeThing:public BaseTable
{
    Q_OBJECT
    int indexToOpen;
public:
    void AfterMakeGui();
    explicit OpenSomeThing(QWidget *parent ,int indexToOpen);
signals:
    void sig_OpenSomeThing(QString id);
    void sig_needNewSomeThing();
public slots:
    void action_Open();
    void action_addRow();
};
#endif // BASETABLE_H
