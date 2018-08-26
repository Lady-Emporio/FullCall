#include "dealers.h"

void Dealers::makeGui()
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    QHBoxLayout * row1Layout=new QHBoxLayout(this);
    QHBoxLayout * row2Layout=new QHBoxLayout(this);

    QLabel *codeLabel=new QLabel("Код",this);
    QLabel *nameLabel=new QLabel("Наименование",this);
    QLabel *commentLabel=new QLabel("Комментарий",this);
    QLabel *activePhoneLabel=new QLabel("Активный телефон",this);
    QLabel *distryPhoneLabel=new QLabel("Дистри телефон",this);

    codeEdit=new QLineEdit(this);
    nameEdit=new QLineEdit(this);
    commentEdit=new QTextEdit(this);
    activePhoneEdit=new QLineEdit(this);
    distryPhoneEdit=new QLineEdit(this);

    row1Layout->addWidget(codeLabel);
    row1Layout->addWidget(codeEdit);
    row1Layout->addWidget(nameLabel);
    row1Layout->addWidget(nameEdit);

    row2Layout->addWidget(activePhoneLabel);
    row2Layout->addWidget(activePhoneEdit);
    row2Layout->addWidget(distryPhoneLabel);
    row2Layout->addWidget(distryPhoneEdit);

    mainLayout->addLayout(row1Layout);
    mainLayout->addWidget(commentLabel);
    mainLayout->addWidget(commentEdit);
    mainLayout->addLayout(row2Layout);
    this->setLayout(mainLayout);

    QHBoxLayout * hideSubTableLayout=new QHBoxLayout(this);
    mainLayout->addLayout(hideSubTableLayout);
    hideFullCallButton=new QPushButton("hide full call",this);
    hideEmailButton=new QPushButton("hide email",this);
    hideSubTableLayout->addWidget(hideFullCallButton);
    hideSubTableLayout->addWidget(hideEmailButton);
    QHBoxLayout * SubTableLayout=new QHBoxLayout(this);
    mainLayout->addLayout(SubTableLayout);
    //email
    email=new SubTable(this,1);
    email->indexParent=4;
    email->parent_code=code;
    email->modelRelational=nullptr;
    email->modelTable=new QSqlTableModel(this,Settings::S()->_db);
    email->modelTable->setTable("email");
    //email->modelTable->setFilter("_parent='"+Settings::shieldInection(code)+"'");
    email->makeGui();
    email->action_refreshModel();
    email->filter->hide();
    email->setFilterButton->hide();
    email->commitButton->hide();
    email->tableView->hideColumn(0);
    email->tableView->hideColumn(4);
    // full call
    full_call=new SubTable(this,1);
    full_call->indexParent=4;
    full_call->parent_code=code;
    full_call->modelRelational=nullptr;
    full_call->modelTable=new QSqlTableModel(this,Settings::S()->_db);
    full_call->modelTable->setTable("full_call");
    //full_call->modelTable->setFilter("_parent='"+Settings::shieldInection(code)+"'");
    full_call->makeGui();
    full_call->action_refreshModel();
    full_call->filter->hide();
    full_call->setFilterButton->hide();
    full_call->commitButton->hide();
    full_call->tableView->hideColumn(0);
    full_call->tableView->hideColumn(4);
    //end full call
    SubTableLayout->addWidget(full_call);
    SubTableLayout->addWidget(email);

    QPushButton*commitButton=new QPushButton("Commit all",this);
    QPushButton*defaultButton=new QPushButton("refresh all",this);
    mainLayout->addWidget(commitButton);
    mainLayout->addWidget(defaultButton);
    connect(hideFullCallButton, SIGNAL(clicked()), this, SLOT(action_HideFullCall()));
    connect(hideEmailButton, SIGNAL(clicked()), this, SLOT(action_HideEmail()));
    connect(commitButton, SIGNAL(clicked()), this, SLOT(action_WriteInDB()));
    connect(defaultButton, SIGNAL(clicked()), this, SLOT(fillAll()));
}

Dealers::Dealers(QWidget *parent,QString code) : QWidget(parent),code(code)
{
    makeGui();
    fillAll();
}

void Dealers::fillAll()
{
    codeEdit->clear();
    nameEdit->clear();
    activePhoneEdit->clear();
    distryPhoneEdit->clear();
    commentEdit->clear();

    QSqlQuery query(Settings::S()->_db);
    query.prepare("SELECT * FROM dealers WHERE _code=:code");
    query.bindValue(":code",Settings::shieldInection(code));
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText(Settings::S()->_db.lastError().text()+" |\n"+query.lastError().text()+"|\n"+query.lastQuery());
        msgBox.exec();
        return;
    }
    query.next();
    codeEdit->setText( query.value("_code").toString());
    nameEdit->setText( query.value("_name").toString());
    activePhoneEdit->setText( query.value("_activePhone").toString());
    distryPhoneEdit->setText( query.value("_distryPhone").toString());
    commentEdit->setPlainText( query.value("_comment").toString());
    email->modelTable->setFilter("_parent='"+Settings::shieldInection(code)+"'");
    full_call->modelTable->setFilter("_parent='"+Settings::shieldInection(code)+"'");
    email->modelTable->select();
    full_call->modelTable->select();
}

void Dealers::action_HideFullCall()
{
    if(full_call->isHidden()){
        full_call->show();
        hideFullCallButton->setText("hide full call");
    }else{
        full_call->hide();
        hideFullCallButton->setText("Show full call");
    }
}

void Dealers::action_HideEmail()
{
    if(email->isHidden()){
        email->show();
        hideEmailButton->setText("hide email");
    }else{
        email->hide();
        hideEmailButton->setText("Show email");
    }
}

void Dealers::action_WriteInDB()
{
    email->action_commitModel();
    full_call->action_commitModel();
    QSqlQuery query(Settings::S()->_db);
    query.prepare("UPDATE dealers SET _code=:newCode,_name=:name,_comment=:comment,_activePhone=:activePhone,"
                  "_distryPhone=:distryPhone WHERE _code=:oldCode;");
    query.bindValue(":oldCode",code);
    query.bindValue(":distryPhone",distryPhoneEdit->text());
    query.bindValue(":activePhone",activePhoneEdit->text());
    query.bindValue(":comment",commentEdit->toPlainText());
    query.bindValue(":name",nameEdit->text());
    query.bindValue(":newCode",codeEdit->text());

    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Error with update dealers:"+code+" |\n"+query.lastError().text()+" |\n"+query.lastQuery());
        msgBox.exec();
        return;
    }
    code=codeEdit->text();
    email->parent_code=code;
    full_call->parent_code=code;
    this->fillAll();
}

void DealersList::makeGui()
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    QMenuBar * mainMenu=new QMenuBar(this);
    mainMenu->addAction("Open",this,SLOT(action_Open()));
    mainMenu->addAction("Refresh",this,SLOT(action_refresh()));
    mainMenu->addAction("addNew",this,SLOT(action_AddNew()));
    mainLayout->setMenuBar(mainMenu);

    model=new QSqlRelationalTableModel(mainLayout,Settings::S()->_db);
    model->setTable("dealers");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    tableView=new QTableView(this);
    tableView->setModel(model);
    tableView->setSortingEnabled(true);
    QHBoxLayout *filterLayout=new QHBoxLayout(this);
    filter=new QLineEdit("_code LIKE '%00%'",this);
    QPushButton*filterButton=new QPushButton("filter",this);
    filterLayout->addWidget(filter);
    filterLayout->addWidget(filterButton);
    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(tableView);
    QPushButton*commitButton=new QPushButton("Commit all",this);
    mainLayout->addWidget(commitButton);
    connect(commitButton, SIGNAL(clicked()), this, SLOT(action_CommitDealerList()));
    connect(filterButton, SIGNAL(clicked()), this, SLOT(action_setFilter()));
}

DealersList::DealersList(QWidget *parent): QWidget(parent)
{
    makeGui();
    action_refresh();
}

void DealersList::action_Open()
{
    if(tableView->currentIndex()!=QModelIndex()){
        QString code=tableView->model()->index(tableView->currentIndex().row(),0).data().toString();
        emit sig_OpenDealer(code);
    }
}

void DealersList::action_refresh()
{
    model->select();
}

void DealersList::action_CommitDealerList()
{
    if(!model->submitAll()){
        QMessageBox msgBox;
        msgBox.setText(model->lastError().text());
        msgBox.exec();
    }
    model->select();
}

void DealersList::action_AddNew()
{
    model->insertRow(model->rowCount());
}

void DealersList::action_setFilter()
{
    model->setFilter(filter->text());
}
