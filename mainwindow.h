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
class MainWindow : public QMainWindow
{
    Q_OBJECT
    QMdiArea * mdiArea;
    void makeGui();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void action_Settings();
    void action_CarsList();
    void action_ColorsList();
    void action_CarColor();
    void action_ManagersList();
    void action_DealersList();
    void get_sig_OpenDealer(QString code);
};

#endif // MAINWINDOW_H
