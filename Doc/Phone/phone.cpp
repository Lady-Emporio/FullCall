#include "phone.h"

void Phone::makeGui()
{
    qDebug()<<orderParent;
    idRec=new QLabel(this);
    QLabel *ordersRec=new QLabel(QString("").setNum(orderParent),this);
    f_statuRec=new QComboBox(this);
    QStringList statusList;
    statusList<<"Search!!!"<<"Cancel"<<"Found"<<"Wait";
    f_statuRec->insertItems(0,statusList);
    SubTableOnlyParent *call=new SubTableOnlyParent(this,1,QString("").setNum(orderParent));
    call->modelRelational=nullptr;
    call->modelTable= new QSqlTableModel(this,Settings::S()->_db);
    call->modelTable->setTable("calls");
    call->makeGui();
    call->hideFilter();
    call->modelTable->setFilter("_phone='"+QString("").setNum(orderParent)+"'");
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    QMenuBar *mainMenu=new QMenuBar(this);
    mainLayout->setMenuBar(mainMenu);

    QHBoxLayout *r2Layout=new QHBoxLayout(this);
    QVBoxLayout *r3Layout=new QVBoxLayout(this);
    r2Layout->addLayout(r3Layout);
    r2Layout->addWidget(f_statuRec);

    r3Layout->addWidget(idRec);
    r3Layout->addWidget(ordersRec);
    mainLayout->addLayout(r2Layout);
    mainLayout->addWidget(call);
}

Phone::Phone(QWidget *parent,int orderParent) : QWidget(parent),orderParent(orderParent)
{
    makeGui();
//    if(orderParent!=0){
//        action_refreshAll();
//    }
}

void Phone::action_refreshAll()
{
     QSqlQuery query(Settings::S()->_db);
    query.prepare("SELECT _id,_f_status FROM phone WHERE _orders=:orders");
    query.bindValue(":orders",orderParent);
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText(Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    query.next();
    id=query.value("_id").toString();
    idRec->setText(id);
    f_statuRec->setCurrentText(query.value("_f_status").toString());
}
