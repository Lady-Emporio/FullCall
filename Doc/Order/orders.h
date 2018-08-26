#ifndef ORDERS_H
#define ORDERS_H

#include "allinclude.h"
#include "Settings/settings.h"
#include "Catalogs/BaseTable/basetable.h"

class MyLabelChoose:public QLabel{
Q_OBJECT
public:
MyLabelChoose(QWidget *parent):QLabel(parent){
    static int counter=0;
    counter+=1;
    this->setObjectName("MyLabelChoose"+QString("").setNum(counter));
    this->setStyleSheet("border:1px solid blue;");
}
void mouseDoubleClickEvent(QMouseEvent *event);
signals:
    void sig_chooseCar(QString nameObject);

};

class Orders : public QWidget
{
    Q_OBJECT
    QLabel * idRec;
    QLabel * dateRec;
    QLabel * presentationRec;
    QComboBox *managerRec;
    QLineEdit *workListRec;
    QLineEdit *clientRec;
    SubTableOnlyParent *colorsRec;
    SubTableOnlyParent *optionsRec;
    QComboBox *statusRec;
    SubTable * timeline;
    void makeGui();
    QString code;
    QMenuBar * mainMenu;
    void makeGuiNewObject();
    QLabel * optionLabel;
    QLabel * colorLabel;
    void makeExistObject();
public:
    MyLabelChoose *modelRec;
    explicit Orders(QWidget *parent, QString code);

signals:
    void sig_closeNewOrderAfterCommit();
public slots:
    void action_CreateNewOrder();
    void get_sig_chooseCar(QString toObjectName,QString code);
    void action_refreshALl();
    void action_UpdateOrder();
};

#endif // ORDERS_H
