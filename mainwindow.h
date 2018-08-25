#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "allinclude.h"
#include "Catalogs/Cars/carslist.h"
#include <Settings/settings.h>
#include <Settings/settings_gui.h>
#include "Catalogs/Cars/carschoose.h"

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
};

#endif // MAINWINDOW_H
