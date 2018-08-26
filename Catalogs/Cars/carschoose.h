#ifndef CARSCHOOSE_H
#define CARSCHOOSE_H

#include "allinclude.h"
#include "Settings/settings.h"
class TableChoose:public QTableView
{
Q_OBJECT
    QString senderName;
public:
    TableChoose(QWidget *parent,QString senderName): QTableView(parent),senderName(senderName){}
    void mouseDoubleClickEvent(QMouseEvent *event);
};



class CarsChoose : public QWidget
{
    Q_OBJECT
    void makeGui();
    QString defaultFilter;
    QSqlRelationalTableModel *model;
    QString senderName;
public:
    TableChoose *tableView;
    QStringList historyFilters;
    QPushButton * forFilter;
    explicit CarsChoose(QWidget *parent ,QString senderName);
public slots:
    void action_backToFilters();
signals:
    void sig_chooseCode(QString sender_name,QString code);
};

#endif // CARSCHOOSE_H
