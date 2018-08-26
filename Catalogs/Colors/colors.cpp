#include "colors.h"

Colors::Colors(QWidget *parent) : QWidget(parent)
{
makeGui();
action_refreshModel();
}
void Colors::makeGui()
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

    model = new QSqlTableModel(this,Settings::S()->_db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("colors");
    QTableView *tableView=new QTableView(this);
    tableView->setModel(model);
    mainLayout->addWidget(tableView);

    QPushButton * commitButton=new QPushButton("commit",this);
    mainLayout->addWidget(commitButton);
    mainMenu->addAction("Add row",this,SLOT(action_addRow()));
    mainMenu->addAction("Refresh",this,SLOT(action_refreshModel()));
    connect(commitButton, SIGNAL(clicked()), this, SLOT(action_commitModel()));
    connect(setFilterButton, SIGNAL(clicked()), this, SLOT(action_filter()));
}

void Colors::action_addRow()
{
    model->insertRow(model->rowCount());
}

void Colors::action_refreshModel()
{
    filter->setText("");
    model->select();
}

void Colors::action_commitModel()
{
    if(!model->submitAll()){
        QMessageBox msgBox;
        msgBox.setText(model->lastError().text());
        msgBox.exec();
    }
}

void Colors::action_filter()
{
    model->setFilter(filter->text());
    model->select();
}
