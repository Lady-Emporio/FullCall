#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "allinclude.h"
#include "Catalogs/Cars/carslist.h"
#include <Settings/settings.h>
#include <Settings/settings_gui.h>
#include "Catalogs/Cars/carschoose.h"
#include "Catalogs/Colors/colors.h"
#include "Catalogs/Cars_colors/carscolors.h"
#include "Catalogs/Managers/managers.h"
#include "Catalogs/Dealers/dealers.h"
#include "Doc/Order/orders.h"
#include "Doc/Phone/phoneslist.h"
#include "Doc/Phone/phone.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
    void makeGui();
public:
    QMdiArea * mdiArea;
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void sig_chooseCar(QString toObjectName,QString code,QString carName);
private slots:
    void action_Settings();
    void action_CarsList();
    void action_ColorsList();
    void action_CarColor();
    void action_ManagersList();
    void action_DealersList();
    void get_sig_OpenDealer(QString code);
    void action_OrdersList();
    void get_sig_NewOrder();
    void get_sig_chooseCar(QString senderName);
    void get_sig_fromChooseToOrder(QString senderName, QString code,QString carName);
    void get_sig_closeNewOrderAfterCommit();
    void get_sig_OpenOrder(QString code);
    void action_PhonesList();
public slots:
    void open_PhonesList(QString parent="");
};

#endif // MAINWINDOW_H
