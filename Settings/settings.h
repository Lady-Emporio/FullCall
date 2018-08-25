#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMap>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlQuery>
#include <QSqlError>

class Settings
{
    QMap<QString,QString>parameters;
    QSqlDatabase _db;
    Settings();
    bool openDB();
    void readParamsFromJson();
    void writeParamsToJson();
    void insertParamsInJson(QString key, QString value);
    void SetDefaultParams();
public:
    static QStringList keys();
    static Settings *S();
    static QString get(QString par);
    static void set(QMap<QString,QString>par);
    static void GetErrorMessage(QSqlQuery *query=nullptr,QString transaction="");
    static QSqlDatabase * db();
};

#endif // SETTINGS_H
