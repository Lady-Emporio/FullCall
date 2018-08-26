#include "orders.h"

void Orders::makeGui()
{
    idRec=new QLabel(this);
    dateRec=new QLabel(this);
    presentationRec=new QLabel(this);
    managerRec=new QComboBox(this);
    statusRec=new QComboBox(this);
    QSqlTableModel *modelManagers=new QSqlTableModel(this,Settings::S()->_db);
    modelManagers->setTable("managers");
    modelManagers->select();
    managerRec->setModel(modelManagers);
    managerRec->setModelColumn(0);
    workListRec=new QLineEdit(this);
    clientRec=new QLineEdit(this);
    modelRec=new MyLabelChoose(this);

    statusRec->insertItem(0,"Search!!!");
    statusRec->insertItem(1,"Cancel");
    statusRec->insertItem(2,"Found");
    statusRec->insertItem(3,"Wait");

    colorsRec=new SubTableOnlyParent(this,2,code);
    colorsRec->modelRelational=new QSqlRelationalTableModel(this,Settings::S()->_db);
    colorsRec->modelTable=nullptr;
    colorsRec->modelRelational->setTable("orders_color");
    colorsRec->modelRelational->setRelation(1, QSqlRelation("colors", "_id", "_name"));
    colorsRec->makeGui();
    colorsRec->action_refreshModel();
    colorsRec->commitButton->hide();
    colorsRec->tableView->hideColumn(0);
    colorsRec->hideFilter();

    optionsRec=new SubTableOnlyParent(this,2,code);
    optionsRec->modelRelational=nullptr;
    optionsRec->modelTable=new QSqlTableModel(this,Settings::S()->_db);
    optionsRec->modelTable->setTable("orders_option");
    optionsRec->makeGui();
    optionsRec->commitButton->hide();
    optionsRec->tableView->hideColumn(0);
    optionsRec->hideFilter();

    timeline=new SubTable(this,1);
    timeline->parent_code=code;
    timeline->indexParent=3;
    timeline->modelRelational=nullptr;
    timeline->modelTable=new QSqlTableModel(this,Settings::S()->_db);
    timeline->modelTable->setTable("order_timeline");
    timeline->makeGui();
    timeline->commitButton->hide();
    timeline->hideFilter();

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    mainMenu=new QMenuBar(this);
    mainLayout->setMenuBar(mainMenu);

    QHBoxLayout *codeDateStatusLayout=new QHBoxLayout(this);
    codeDateStatusLayout->addWidget(new QLabel("Id",this));
    codeDateStatusLayout->addWidget(idRec);
    codeDateStatusLayout->addWidget(new QLabel("Date",this));
    codeDateStatusLayout->addWidget(dateRec);
    codeDateStatusLayout->addWidget(statusRec);
    QHBoxLayout *rightAndLeftLayout=new QHBoxLayout(this);
    QVBoxLayout *leftLayout=new QVBoxLayout(this);
    QVBoxLayout *rightLayout=new QVBoxLayout(this);
    rightAndLeftLayout->addLayout(leftLayout);
    rightAndLeftLayout->addLayout(rightLayout);

    QHBoxLayout *managersLayout=new QHBoxLayout(this);
    managersLayout->addWidget(new QLabel("Managers",this));
    managersLayout->addWidget(managerRec);
    leftLayout->addLayout(managersLayout);

    QHBoxLayout *clientsLayout=new QHBoxLayout(this);
    clientsLayout->addWidget(new QLabel("Client",this));
    clientsLayout->addWidget(clientRec);
    leftLayout->addLayout(clientsLayout);

    QHBoxLayout *workListLayout=new QHBoxLayout(this);
    workListLayout->addWidget(new QLabel("Work List",this));
    workListLayout->addWidget(workListRec);
    leftLayout->addLayout(workListLayout);

    QHBoxLayout *modelLayout=new QHBoxLayout(this);
    modelLayout->addWidget(new QLabel("Car",this));
    modelLayout->addWidget(modelRec);
    leftLayout->addLayout(modelLayout);

    colorLabel=new QLabel("Color",this);
    rightLayout->addWidget(colorLabel);
    rightLayout->addWidget(colorsRec);
    optionLabel=new QLabel("Option",this);
    rightLayout->addWidget(optionLabel);
    rightLayout->addWidget(optionsRec);
    leftLayout->addWidget(timeline);

    mainLayout->addWidget(presentationRec);
    mainLayout->addLayout(codeDateStatusLayout);
    mainLayout->addLayout(rightAndLeftLayout);
}

void Orders::makeGuiNewObject()
{
    mainMenu->addAction("Create",this,SLOT(action_CreateNewOrder()));
    colorsRec->hide();
    timeline->hide();
    optionsRec->hide();
    optionLabel->hide();
    colorLabel->hide();

    QString time=QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss");
    dateRec->setText(time);
}

void Orders::makeExistObject()
{
    mainMenu->addAction("Update",this,SLOT(action_UpdateOrder()));
    mainMenu->addAction("Refresh",this,SLOT(action_refreshALl()));
    colorsRec->modelRelational->setFilter("_parent='"+code +"'");
    optionsRec->modelTable->setFilter("_parent='"+code +"'");
    timeline->modelTable->setFilter("_parent='"+code +"'");
}

Orders::Orders(QWidget *parent,QString code) : QWidget(parent),code(code)
{
    makeGui();
    if(code==""){
        makeGuiNewObject();
    }else{
        action_refreshALl();
        makeExistObject();
        action_refreshALl();
    }
}

void Orders::action_CreateNewOrder()
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("INSERT INTO orders(_date,_manager,_workList,_client,_model,_status) VALUES "
                  " (:_date,:_manager,:_workList,:_client,:_model,:_status);");
    query.bindValue(":_date",dateRec->text());
    query.bindValue(":_manager",managerRec->currentText());
    query.bindValue(":_workList",workListRec->text());
    query.bindValue(":_client",clientRec->text());
    query.bindValue(":_model",modelRec->text());
    query.bindValue(":_status",statusRec->currentText());
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText(Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    Settings::S()->_db.commit();
    emit sig_closeNewOrderAfterCommit();
}

void Orders::get_sig_chooseCar(QString toObjectName, QString code)
{
    if(this->modelRec->objectName()==toObjectName){
        this->modelRec->setText(code);
    }
}

void Orders::action_refreshALl()
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("SELECT _id,_date,_manager,_workList,_client,_model,_status,_presentation FROM orders WHERE _id=:code");
    query.bindValue(":code",code);
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText(Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    query.next();
    idRec->setText(query.value("_id").toString());
    dateRec->setText(query.value("_date").toString());
    managerRec->setCurrentText(query.value("_manager").toString());
    workListRec->setText(query.value("_workList").toString());
    clientRec->setText(query.value("_client").toString());
    modelRec->setText(query.value("_model").toString());
    statusRec->setCurrentText(query.value("_status").toString());
    presentationRec->setText(query.value("_presentation").toString());

    timeline->action_refreshModel();
    optionsRec->action_refreshModel();
    colorsRec->action_refreshModel();

}

void Orders::action_UpdateOrder()
{
    QSqlQuery query(Settings::S()->_db);
    query.prepare("UPDATE orders SET _manager=:_manager,_workList=:_workList,_client=:_client,_model=:_model,_status=:_status WHERE _id=:id");
    query.bindValue(":_manager",managerRec->currentText());
    query.bindValue(":_workList",workListRec->text());
    query.bindValue(":_client",clientRec->text());
    query.bindValue(":_model",modelRec->text());
    query.bindValue(":_status",statusRec->currentText());
    query.bindValue(":id",code);
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText(Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    Settings::S()->_db.commit();
    timeline->action_commitModel();
    optionsRec->action_commitModel();
    colorsRec->action_commitModel();
}

void MyLabelChoose::mouseDoubleClickEvent(QMouseEvent *event)
{
    QString thisName=objectName();
    emit sig_chooseCar(thisName);
}
