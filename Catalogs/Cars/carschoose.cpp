#include "carschoose.h"



CarsChoose::CarsChoose(QWidget *parent) : QWidget(parent)
{
    makeGui();
}

void CarsChoose::makeGui()
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    model = new QSqlRelationalTableModel(this,Settings::S()->_db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("cars");
    //model->setRelation(2, QSqlRelation("cars", "_code", "_name"));
    model->select();
    QTableView *tableView=new QTableView(this);
    tableView->setModel(model);
    mainLayout->addWidget(tableView);
}
