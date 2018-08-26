#include "managers.h"

Managers::Managers(QWidget *parent) : BaseTable(parent)
{
    modelTable=new QSqlTableModel(this,Settings::S()->_db);;
    modelRelational=nullptr;
    modelTable->setTable("managers");
    this->makeGui();
    action_refreshModel();
}
