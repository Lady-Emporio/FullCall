#include "settings.h"

Settings::Settings()
{
    SetDefaultParams();
    readParamsFromJson();
    if(!openDB()){
        return;
    }
}

bool Settings::openDB()
{
    QString transaction_name="Settings";
     _db = QSqlDatabase::addDatabase("QSQLITE",transaction_name);
     _db.setDatabaseName(parameters["path/to/db"]);
     if (!_db.open()){
        GetErrorMessage(nullptr,transaction_name);
        return false;
    };
     _db.exec("PRAGMA foreign_keys = ON;");
     return true;
}

void Settings::readParamsFromJson()
{
    QFile file("style.json");
    if(!file.exists()){
        writeParamsToJson();
        return;
    }
    file.open(QIODevice::ReadOnly);
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject root=document.object();

    QMapIterator<QString, QString> i(parameters);
    while (i.hasNext()) {
        i.next();
        if(!root.contains(i.key())){
            insertParamsInJson(i.key(),i.value());
        }else{
            parameters[i.key()]=root[i.key()].toString();
        }
    };
}

void Settings::writeParamsToJson()
{
    QMapIterator<QString, QString> i(parameters);
    QJsonObject root;
    while (i.hasNext()) {
        i.next();
        QJsonValue JSvalue(i.value());
        root.insert(i.key(), JSvalue);
    };
    QJsonDocument new_doc(root);
    QFile jsonFile("style.json");
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(new_doc.toJson());
    jsonFile.close();
}

void Settings::insertParamsInJson(QString key,QString value)
{
    QFile file("style.json");
    file.open(QIODevice::ReadOnly);
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    QJsonObject root=document.object();

    QJsonValue JSvalue(value);
    root.insert(key, JSvalue);

    QJsonDocument new_doc(root);
    QFile jsonFile("style.json");
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(new_doc.toJson());
    jsonFile.close();
}

void Settings::SetDefaultParams()
{
    parameters.insert("path/to/db","./main.sqlite");
    parameters.insert("app/image","./image.png");
}

QStringList Settings::keys()
{
    return Settings::S()->parameters.keys();
}

Settings *Settings::S()
{
    static Settings * s=new Settings;
    return s;
}

QString Settings::get(QString par)
{
    Settings * s=S();
    if(s->parameters.contains(par)){
        return s->parameters.value(par);
    }else{
        QMessageBox msgBox;
        msgBox.setText("In settings not:"+par);
        msgBox.exec();
    }
    return "";
}

void Settings::set(QMap<QString, QString> par)
{
    Settings * s=S();
    QStringList keys=par.keys();
    for(QString key: keys){
        if(s->parameters.contains(key)){
            s->parameters[key]=par.value(key);
        }else{
            QMessageBox msgBox;
            msgBox.setText("In settings not:"+key);
            msgBox.exec();
        }
    }
}

void Settings::GetErrorMessage(QSqlQuery *query, QString transaction)
{
    Settings *s=Settings::S();
    QString error;
    error+=transaction+" |\n";
    error+=s->_db.lastError().text()+" |\n";
    if(query!=nullptr){
        error+=query->lastError().text()+" |\n";
        error+=query->lastQuery()+" |\n";
    }
    QMessageBox msgBox;
    msgBox.setText(error);
    msgBox.exec();
}

QSqlDatabase *Settings::db()
{
     return & Settings::S()->_db;
}
