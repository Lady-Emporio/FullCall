#include "mainwindow.h"



void MainWindow::makeGui()
{

    mdiArea=new QMdiArea(this);
    this->setCentralWidget(mdiArea);

    QMenuBar * mainMenu=new QMenuBar(this);
    this->setMenuBar(mainMenu);
    mainMenu->addAction("Settings",this,SLOT(action_Settings()));
    QMenu *catalogs=new QMenu("Catalogs",mainMenu);
    mainMenu->addMenu(catalogs);
    catalogs->addAction("Cars",this,SLOT(action_CarsList()));
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
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
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
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
    CarsList *cars=new CarsList(subWindow);
    subWindow->setWidget(cars);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}
