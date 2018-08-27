#include "basetable.h"

void BaseTable::makeGui()
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    mainMenu=new QMenuBar(this);
    mainLayout->setMenuBar(mainMenu);

    QHBoxLayout *filterLayout=new QHBoxLayout(this);
    filter=new QLineEdit(this);
    setFilterButton=new QPushButton("Filter",this);
    filterLayout->addWidget(filter);
    filterLayout->addWidget(setFilterButton);
    mainLayout->addLayout(filterLayout);

    tableView=new QTableView(this);
    tableView->setSortingEnabled(true);
    if(modelTable!=nullptr){
        modelTable->setEditStrategy(QSqlTableModel::OnManualSubmit);
        tableView->setModel(modelTable);
        mainLayout->addWidget(tableView);
    }else{
        modelRelational->setEditStrategy(QSqlTableModel::OnManualSubmit);
        tableView->setModel(modelRelational);
        tableView->setItemDelegate(new QSqlRelationalDelegate(tableView));
    }
    mainLayout->addWidget(tableView);
    commitButton=new QPushButton("commit",this);
    mainLayout->addWidget(commitButton);
    mainMenu->addAction("New",this,SLOT(action_addRow()));
    mainMenu->addAction("Refresh",this,SLOT(action_refreshModel()));
    connect(commitButton, SIGNAL(clicked()), this, SLOT(action_commitModel()));
    connect(setFilterButton, SIGNAL(clicked()), this, SLOT(action_filter()));
}

BaseTable::BaseTable(QWidget *parent) : QWidget(parent)
{

}

void BaseTable::hideFilter()
{
    filter->hide();
    setFilterButton->hide();
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
        modelRelational->setData(modelRelational->index(newRow,indexParent),parent_code);
    }
}

SubTableOnlyParent::SubTableOnlyParent(QWidget *parent, int indexParent, QString parent_code):BaseTable(parent),indexParent(indexParent),parent_code(parent_code)
{

}

void SubTableOnlyParent::action_addRow()
{
    if(modelTable!=nullptr){
        int newRow=modelTable->rowCount();
        modelTable->insertRow(newRow);
        modelTable->setData(modelTable->index(newRow,indexParent),parent_code);
    }else{
        int newRow=modelRelational->rowCount();
        modelRelational->insertRow(newRow);
        modelRelational->setData(modelRelational->index(newRow,indexParent),parent_code);
    }
}

OpenSomeThing::OpenSomeThing(QWidget *parent, int indexToOpen):BaseTable(parent),indexToOpen(indexToOpen)
{
}

void OpenSomeThing::AfterMakeGui()
{
    mainMenu->addAction("Open",this,SLOT(action_Open()));
}

void OpenSomeThing::action_Open()
{
    if(tableView->currentIndex()!=QModelIndex()){
        QString code=tableView->model()->index(tableView->currentIndex().row(),indexToOpen).data().toString();
        emit sig_OpenSomeThing(code);
    }
}

void OpenSomeThing::action_addRow()
{
    emit sig_needNewSomeThing();
}
