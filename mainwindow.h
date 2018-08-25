#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <Settings/settings.h>
#include <Settings/settings_gui.h>
#include <QDebug>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMenuBar>

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
};

#endif // MAINWINDOW_H
