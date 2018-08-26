#include "basetable.h"

void BaseTable::makeGui()
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    QMenuBar * mainMenu=new QMenuBar(this);
    mainLayout->setMenuBar(mainMenu);

    QHBoxLayout *filterLayout=new QHBoxLayout(this);
    filter=new QLineEdit(this);
    setFilterButton=new QPushButton("Filter",this);
    filterLayout->addWidget(filter);
    filterLayout->addWidget(setFilterButton);
    mainLayout->addLayout(filterLayout);

    if(modelTable!=nullptr){
        modelTable->setEditStrategy(QSqlTableModel::OnManualSubmit);
        tableView=new QTableView(this);
        tableView->setSortingEnabled(true);
        tableView->setModel(modelTable);
        mainLayout->addWidget(tableView);
    }else{
        modelRelational->setEditStrategy(QSqlTableModel::OnManualSubmit);
        QTableView *tableView=new QTableView(this);
        tableView->setModel(modelRelational);
        tableView->setSortingEnabled(true);
        tableView->setItemDelegate(new QSqlRelationalDelegate(tableView));
        mainLayout->addWidget(tableView);
    }
    commitButton=new QPushButton("commit",this);
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
    if(modelTable!=nullptr){
        if(!modelTable->select()){
            QMessageBox msgBox;
            msgBox.setText("Error with modelTable:"+modelTable->lastError().text());
            msgBox.exec();
        }
    }else{
        if(!modelRelational->select()){
            QMessageBox msgBox;
            msgBox.setText("Error with modelRelational"+modelRelational->lastError().text());
            msgBox.exec();
        }
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
    if(modelTable!=nullptr){
        modelTable->setFilter(filter->text());
        modelTable->select();
    }else{
        modelRelational->setFilter(filter->text());
        modelRelational->select();
    }
}

SubTable::SubTable(QWidget *parent, int indexColumnDate):BaseTable(parent),indexColumnDate(indexColumnDate)
{

}

void SubTable::action_addRow()
{
    QString time=QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss");
    if(modelTable!=nullptr){
        int newRow=modelTable->rowCount();
        modelTable->insertRow(newRow);
        modelTable->setData(modelTable->index(newRow,indexColumnDate),time);
        modelTable->setData(modelTable->index(newRow,indexParent),parent_code);
    }else{
        int newRow=modelRelational->rowCount();
        modelRelational->insertRow(newRow);
        modelRelational->setData(modelRelational->index(newRow,indexColumnDate),time);
        modelTable->setData(modelTable->index(newRow,indexParent),parent_code);
    }
}
