#ifndef DEALERS_H
#define DEALERS_H

#include "allinclude.h"
#include "Settings/settings.h"
#include "Catalogs/BaseTable/basetable.h"
class DealersList : public QWidget
{
    Q_OBJECT
    void MakeGui();
    QTableView *tableView;
    QSqlRelationalTableModel *model;
    QLineEdit * filter;
    void makeGui();
public:
    explicit DealersList(QWidget *parent = 0);

signals:
    void sig_OpenDealer(QString code);
public slots:
    void action_Open();
    void action_refresh();
    void action_CommitDealerList();
    void action_AddNew();
    void action_setFilter();
};


class Dealers : public QWidget
{
    Q_OBJECT
    void makeGui();
    SubTable *email;
    SubTable *full_call;
    QLineEdit *codeEdit;
    QLineEdit*nameEdit;
    QLineEdit*activePhoneEdit;
    QLineEdit*distryPhoneEdit;
    QTextEdit*commentEdit;
    QString code;
    QPushButton*hideFullCallButton;
    QPushButton*hideEmailButton;
public:
    explicit Dealers(QWidget *parent ,QString code);

signals:

public slots:
    void fillAll();
    void action_HideFullCall();
    void action_HideEmail();
    void action_WriteInDB();
};

#endif // DEALERS_H
