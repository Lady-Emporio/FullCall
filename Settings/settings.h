#ifndef SETTINGS_H
#define SETTINGS_H

#include "allinclude.h"
class Settings
{
    QMap<QString,QString>parameters;
    Settings();
    bool openDB();
    void createTables();
    void readParamsFromJson();
    void writeParamsToJson();
    void insertParamsInJson(QString key, QString value);
    void SetDefaultParams();
public:
    QSqlDatabase _db;
    static QStringList keys();
    static Settings *S();
    static QString get(QString par);
    static void set(QMap<QString,QString>par);
    static void GetErrorMessage(QSqlQuery *query=nullptr,QString transaction="");
};

#endif // SETTINGS_H
