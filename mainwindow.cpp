#include "mainwindow.h"



void MainWindow::makeGui()
{

    mdiArea=new QMdiArea(this);
    this->setCentralWidget(mdiArea);
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QMenuBar * mainMenu=new QMenuBar(this);
    this->setMenuBar(mainMenu);
    mainMenu->addAction("Orders",this,SLOT(action_OrdersList()));
    mainMenu->addAction("Settings",this,SLOT(action_Settings()));
    QMenu *catalogs=new QMenu("Catalogs",mainMenu);
    mainMenu->addMenu(catalogs);
    catalogs->addAction("Cars",this,SLOT(action_CarsList()));
    catalogs->addAction("Colors",this,SLOT(action_ColorsList()));
    catalogs->addAction("Model-colors",this,SLOT(action_CarColor()));
    catalogs->addAction("Managers",this,SLOT(action_ManagersList()));
    catalogs->addAction("Dealers",this,SLOT(action_DealersList()));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    makeGui();

}

MainWindow::~MainWindow()
{

}

void MainWindow::action_Settings()
{
    QString title="Settings";
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            mdiArea->setActiveSubWindow(x);
            x->move(0,0);
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
    subWindow->setWindowTitle(title);
    Settings_gui *setting=new Settings_gui(subWindow);
    subWindow->setWidget(setting);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::action_CarsList()
{
    QString title="Cars list";
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            mdiArea->setActiveSubWindow(x);
            x->move(0,0);
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
    subWindow->setWindowTitle(title);
    CarsList *cars=new CarsList(subWindow);
    subWindow->setWidget(cars);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::action_ColorsList()
{
    QString title="Color list";
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            mdiArea->setActiveSubWindow(x);
            x->move(0,0);
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
    subWindow->setWindowTitle(title);
    Colors *color=new Colors(subWindow);
    subWindow->setWidget(color);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::action_CarColor()
{
    QString title="Model-color";
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            mdiArea->setActiveSubWindow(x);
            x->move(0,0);
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
    subWindow->setWindowTitle(title);
    CarsColors *car_color=new CarsColors(subWindow);
    subWindow->setWidget(car_color);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::action_ManagersList()
{
    QString title="Managers";
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            mdiArea->setActiveSubWindow(x);
            x->move(0,0);
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
    subWindow->setWindowTitle(title);
    Managers *man=new Managers(subWindow);
    subWindow->setWidget(man);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::action_DealersList()
{
    QString title="Dealers list";
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            mdiArea->setActiveSubWindow(x);
            x->move(0,0);
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
    subWindow->setWindowTitle(title);
    DealersList *dealersList=new DealersList(subWindow);
    subWindow->setWidget(dealersList);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();

    connect(dealersList, SIGNAL(sig_OpenDealer(QString)), this, SLOT(get_sig_OpenDealer(QString)));
}

void MainWindow::get_sig_OpenDealer(QString code)
{
    QString title="Dealer:"+code;
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            mdiArea->setActiveSubWindow(x);
            x->move(0,0);
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
    subWindow->setWindowTitle(title);
    Dealers *dealersList=new Dealers(subWindow,code);
    subWindow->setWidget(dealersList);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::action_OrdersList()
{
    QString title="Orders list";
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            mdiArea->setActiveSubWindow(x);
            x->move(0,0);
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
    subWindow->setWindowTitle(title);
    OpenSomeThing *ordersList=new OpenSomeThing(subWindow,0);
    ordersList->modelTable=nullptr;
    ordersList->modelRelational=new QSqlRelationalTableModel(this,Settings::S()->_db);
    ordersList->modelRelational->setTable("orders");
    ordersList->modelRelational->setRelation(0, QSqlRelation("orders", "_id", "_presentation"));
    ordersList->makeGui();
    ordersList->AfterMakeGui();
    ordersList->action_refreshModel();
    ordersList->tableView->setColumnWidth(0,400);

    //ordersList->modelRelational->setFilter("_status='Search!!!'");

    subWindow->setWidget(ordersList);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();

    connect(ordersList, SIGNAL(sig_needNewSomeThing()), this, SLOT(get_sig_NewOrder()));
    connect(ordersList, SIGNAL(sig_OpenSomeThing(QString)), this, SLOT(get_sig_OpenOrder(QString)));


}

void MainWindow::get_sig_NewOrder()
{
    QString title="New order";
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            mdiArea->setActiveSubWindow(x);
            x->move(0,0);
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
    subWindow->setWindowTitle(title);
    Orders *newOrder=new Orders(subWindow,"");
    subWindow->setWidget(newOrder);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();

    connect(newOrder->modelRec, SIGNAL(sig_chooseCar(QString)), this, SLOT(get_sig_chooseCar(QString)));
    connect(this, SIGNAL(sig_chooseCar(QString,QString)), newOrder, SLOT(get_sig_chooseCar(QString,QString)));
    connect(newOrder, SIGNAL(sig_closeNewOrderAfterCommit()), this, SLOT(get_sig_closeNewOrderAfterCommit()));

}

void MainWindow::get_sig_chooseCar(QString senderName)
{
    QString title="ChooseCar:"+senderName;
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            mdiArea->setActiveSubWindow(x);
            x->move(0,0);
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
    subWindow->setWindowTitle(title);
    CarsChoose *carChoose=new CarsChoose(subWindow,senderName);
    subWindow->setWidget(carChoose);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();

    connect(carChoose, SIGNAL(sig_chooseCode(QString,QString)), this, SLOT(get_sig_fromChooseToOrder(QString,QString)));
}

void MainWindow::get_sig_fromChooseToOrder(QString senderName,QString code)
{
    QString title="ChooseCar:"+senderName;
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            x->close();
        };
    };
    emit sig_chooseCar(senderName,code);
}

void MainWindow::get_sig_closeNewOrderAfterCommit()
{
    QString title="New order";
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            x->close();
        };
    };
}

void MainWindow::get_sig_OpenOrder(QString code)
{
    QString title="Order:"+code;
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            mdiArea->setActiveSubWindow(x);
            x->move(0,0);
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
    subWindow->setWindowTitle(title);
    Orders *newOrder=new Orders(subWindow,code);
    subWindow->setWidget(newOrder);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();

    connect(newOrder->modelRec, SIGNAL(sig_chooseCar(QString)), this, SLOT(get_sig_chooseCar(QString)));
    connect(this, SIGNAL(sig_chooseCar(QString,QString)), newOrder, SLOT(get_sig_chooseCar(QString,QString)));
}
