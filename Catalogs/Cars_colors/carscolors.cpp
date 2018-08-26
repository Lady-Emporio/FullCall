#include "carscolors.h"

CarsColors::CarsColors(QWidget *parent) : BaseTable(parent)
{
    modelTable=nullptr;
    modelRelational=new QSqlRelationalTableModel(this,Settings::S()->_db);
    modelRelational->setTable("cars_colors");
    modelRelational->setRelation(1, QSqlRelation("colors", "_id", "_code"));
    this->makeGui();
    action_refreshModel();
}
