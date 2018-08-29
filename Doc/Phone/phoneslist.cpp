#include "phoneslist.h"

PhonesList::PhonesList(QWidget *parent,int orderParent) : BaseTable(parent),orderParent(orderParent)
{
    modelTable=nullptr ;
    modelRelational=new QSqlRelationalTableModel(this,Settings::S()->_db);
    modelRelational->setTable("phone");
    this->makeGui();
    action_refreshModel();
}
