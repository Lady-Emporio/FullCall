#include "basetable.h"

void BaseTable::makeGui()
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    QMenuBar * mainMenu=new QMenuBar(this);
    mainLayout->setMenuBar(mainMenu);

    QHBoxLayout *filterLayout=new QHBoxLayout(this);
    filter=new QLineEdit(this);
    QPushButton * setFilterButton=new QPushButton("Filter",this);
    filterLayout->addWidget(filter);
    filterLayout->addWidget(setFilterButton);
    mainLayout->addLayout(filterLayout);

    //model = new QSqlTableModel(this,Settings::S()->_db);
    if(modelTable!=nullptr){
        modelTable->setEditStrategy(QSqlTableModel::OnManualSubmit);
        QTableView *tableView=new QTableView(this);
        tableView->setModel(modelTable);
        mainLayout->addWidget(tableView);
    }else{
        modelRelational->setEditStrategy(QSqlTableModel::OnManualSubmit);
        QTableView *tableView=new QTableView(this);
        tableView->setModel(modelRelational);
        tableView->setItemDelegate(new QSqlRelationalDelegate(tableView));
        mainLayout->addWidget(tableView);
    }
    QPushButton * commitButton=new QPushButton("commit",this);
    mainLayout->addWidget(commitButton);
    mainMenu->addAction("Add row",this,SLOT(action_addRow()));
    mainMenu->addAction("Refresh",this,SLOT(action_refreshModel()));
    connect(commitButton, SIGNAL(clicked()), this, SLOT(action_commitModel()));
    connect(setFilterButton, SIGNAL(clicked()), this, SLOT(action_filter()));
}

BaseTable::BaseTable(QWidget *parent) : QWidget(parent)
{

}

void BaseTable::action_addRow()
{
    if(modelTable!=nullptr){
        modelTable->insertRow(modelTable->rowCount());
    }else{
        modelRelational->insertRow(modelRelational->rowCount());
    }
}

void BaseTable::action_refreshModel()
{
    filter->setText("");
    if(modelTable!=nullptr){
        modelTable->select();
    }else{
        modelRelational->select();
    }

}

void BaseTable::action_commitModel()
{
    if(modelTable!=nullptr){
        if(!modelTable->submitAll()){
            QMessageBox msgBox;
            msgBox.setText(modelTable->lastError().text());
            msgBox.exec();
        }
    }else{
        if(!modelRelational->submitAll()){
            QMessageBox msgBox;
            msgBox.setText(modelRelational->lastError().text());
            msgBox.exec();
        }
    }

}

void BaseTable::action_filter()
{
    filter->setText("");
    if(modelTable!=nullptr){
        modelTable->select();
    }else{
        modelRelational->select();
    }
}
