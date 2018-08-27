#include "carschoose.h"



CarsChoose::CarsChoose(QWidget *parent, QString senderName) : QWidget(parent),senderName(senderName)
{
    defaultFilter="_folder=1";
    makeGui();

}

void CarsChoose::action_backToFilters()
{
    if(historyFilters.empty()){
        model->setFilter(defaultFilter);
        forFilter->setText(defaultFilter);
    }else{
        historyFilters.pop_back();
        if(historyFilters.isEmpty()){
            model->setFilter(defaultFilter);
            forFilter->setText(defaultFilter);
        }else{
            QString filterLast=historyFilters.takeLast();
            model->setFilter(filterLast);
            forFilter->setText(filterLast);
        }
    }
}

void CarsChoose::makeGui()
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    forFilter=new QPushButton(defaultFilter,this);
    mainLayout->addWidget(forFilter);
    model = new QSqlRelationalTableModel(this,Settings::S()->_db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("cars");
    //model->setRelation(2, QSqlRelation("cars", "_code", "_name"));
    model->select();
    TableChoose *tableView=new TableChoose(this,senderName);
    tableView->setModel(model);
    tableView->setColumnWidth(2,300);
    mainLayout->addWidget(tableView);
    model->setFilter(defaultFilter);

    connect(forFilter, SIGNAL(clicked()), this, SLOT(action_backToFilters()));
}

void TableChoose::mouseDoubleClickEvent(QMouseEvent *event)
{
    QModelIndex currentI=this->indexAt(event->pos());
    if(currentI!=QModelIndex()){
        int row=currentI.row();
        QSqlRelationalTableModel *model=(QSqlRelationalTableModel*)this->model();
        QString toParent=model->index(row,0).data().toString();
        QString filter="_parentCode='"+toParent+"'";
        if(model->filter()!=filter){
            if(model->index(row,4).data().toInt()==1){
                model->setFilter(filter);
                CarsChoose*parentChoose=(CarsChoose*)this->parentWidget();
                parentChoose->forFilter->setText(filter);
                parentChoose->historyFilters.append(filter);
            }else{
                QString chooseIndex=model->index(row,0).data().toString();
                QString chooseName=model->index(row,2).data().toString();
                CarsChoose*parentChoose=(CarsChoose*)this->parentWidget();
                emit parentChoose->sig_chooseCode(senderName,chooseIndex,chooseName);
            }
        }
    }
}
