#include "settings.h"

Settings::Settings()
{
    SetDefaultParams();
    readParamsFromJson();
    if(!openDB()){
        return;
    }
    createTables();
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

void Settings::createTables()
{
    QStringList sqls;
    sqls<<"CREATE TABLE IF NOT EXISTS cars( "
          " _id integer PRIMARY KEY NOT NULL,"
          " _code TEXT NOT NULL, "
          " _name TEXT NOT NULL, "
          " _parentCode TEXT REFERENCES cars(_id) ON UPDATE CASCADE,"
          " _folder integer check( _folder=1 or _folder=0) NOT NULL"
          " ); "
       <<"CREATE UNIQUE INDEX IF NOT EXISTS cars_index ON cars(_code,_name,_parentCode);"
       <<"INSERT OR IGNORE INTO cars(_id,_code,_name,_parentCode,_folder) VALUES "
         "(0,'root','root',0,1);"
       <<"CREATE TABLE IF NOT EXISTS colors( "
         "   _id integer PRIMARY KEY NOT NULL, "
         "  _code text NOT NULL, "
         " _name text NOT NULL "
         "); "
      <<"CREATE UNIQUE INDEX IF NOT EXISTS color_index ON colors(_code,_name);"
     <<"CREATE TABLE IF NOT EXISTS cars_colors(  "
       " _car integer REFERENCES cars(_id)  ON UPDATE CASCADE NOT NULL,  "
       " _color integer REFERENCES colors(_id)  ON UPDATE CASCADE NOT NULL "
       " ); "
    <<"CREATE UNIQUE INDEX IF NOT EXISTS car_color_index ON cars_colors(_car,_color);"
    <<" CREATE TABLE IF NOT EXISTS dealers( "
      " _code TEXT PRIMARY KEY NOT NULL, "
      " _name TEXT, "
      " _comment TEXT, "
      " _activePhone TEXT, "
      " _distryPhone TEXT "
      " ); "
    <<" CREATE TABLE IF NOT EXISTS full_call( "
      " _id INTEGER PRIMARY KEY NOT NULL, "
      " _date TEXT, "
      " _comment TEXT, "
      " _source TEXT, "
      " _parent text REFERENCES dealers(_code) ON UPDATE CASCADE NOT NULL "
      " ); "
    <<" CREATE TABLE IF NOT EXISTS email( "
      " _id INTEGER PRIMARY KEY NOT NULL, "
      " _date TEXT, "
      " _mail TEXT, "
      " _comment TEXT, "
      " _parent text REFERENCES dealers(_code) ON UPDATE CASCADE NOT NULL "
      " ); "
    <<" CREATE TABLE IF NOT EXISTS managers( "
      " _code TEXT PRIMARY KEY NOT NULL, "
      " _fullName TEXT "
      " ); "
     <<"INSERT OR IGNORE INTO managers(_code,_fullName) VALUES ('root','root');"
    <<" CREATE TABLE IF NOT EXISTS orders( "
      " _id INTEGER PRIMARY KEY NOT NULL, "
      " _date TEXT, "
      " _manager TEXT REFERENCES managers(_code) ON UPDATE CASCADE NOT NULL, "
      " _workList TEXT, "
      " _client TEXT, "
      " _model integer REFERENCES cars(_id) ON UPDATE CASCADE NOT NULL, "
      " _mark text CHECK (_mark=0 or _mark=1), "
      " _status text CHECK(_status='' or _status='Search!!!' or _status='Cancel' or _status='Found' or _status='Wait'),"
      " _presentation text "
      " ); "
    <<" CREATE TABLE IF NOT EXISTS orders_color( "
      " _id INTEGER PRIMARY KEY NOT NULL, "
      " _color INTEGER REFERENCES colors(_id) ON UPDATE CASCADE NOT NULL, "
      " _parent integer REFERENCES orders(_id) ON UPDATE CASCADE NOT NULL "
      " ); "
    <<" CREATE TABLE IF NOT EXISTS orders_option( "
      " _id INTEGER PRIMARY KEY NOT NULL, "
      " _option TEXT NOT NULL,"
      " _parent integer REFERENCES orders(_id) ON UPDATE CASCADE NOT NULL "
      " ); "
    <<" CREATE TABLE IF NOT EXISTS order_timeline( "
      "_id INTEGER PRIMARY KEY NOT NULL, "
      " _date TEXT, "
      " _comment TEXT,"
      " _parent integer REFERENCES orders(_id) ON UPDATE CASCADE NOT NULL "
      " ); "
    <<" CREATE TRIGGER IF NOT EXISTS orders_presentation_inser AFTER INSERT ON orders "
      " BEGIN  "
      "     UPDATE orders SET _presentation=NEW._manager||' for '||NEW._client||' in '||NEW._workList; "
      " END; "
    <<" CREATE TRIGGER IF NOT EXISTS orders_presentation_update AFTER UPDATE ON orders "
      " BEGIN  "
      "     UPDATE orders SET _presentation=NEW._manager||' for '||NEW._client||' in '||NEW._workList; "
      " END; "
    <<" CREATE TABLE IF NOT EXISTS phone( "
      " _id INTEGER PRIMARY KEY NOT NULL, "
      " _orders INTEGER REFERENCES orders(_id ) ON UPDATE CASCADE NOT NULL, "
      " _f_status TEXT CHECK(_f_status in ('Search!!!','Cancel','Found','Wait') ) );"
    <<" CREATE TABLE IF NOT EXISTS calls( "
      " _id INTEGER PRIMARY KEY NOT NULL, "
      " _phone INTEGER REFERENCES phone(_id) ON UPDATE CASCADE NOT NULL, "
      " _vinCar TEXT, "
      " _code_dealer TEXT, "
      " _blockCar TEXT, "
      " _dateCar TEXT, "
      " _modelCar TEXT, "
      " _optionCar TEXT, "
      " _colorCar TEXT, "
      " _dateTalk TEXT, "
      " _colorTalk TEXT CHECK(_colorTalk in ('','Красный','Зеленый','Синий','Коричневый','Желтый','Фиолетовый') ), "
      " _commentTalk TEXT "
      " ); "
    ;

    for(QString sql:sqls){
        QSqlQuery query(_db);
        if(!query.exec(sql)){
            QMessageBox msgBox;
            msgBox.setText(_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
            msgBox.exec();
            return;
        }
    }
    _db.commit();
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
    s->writeParamsToJson();
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

QString Settings::shieldInection(QString text)
{
    text=text.replace(";","");
    return text;
}
