#-------------------------------------------------
#
# Project created by QtCreator 2018-08-25T12:57:27
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = as1C
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Settings/settings.cpp \
    Settings/settings_gui.cpp \
    Catalogs/Cars/carslist.cpp \
    Catalogs/Cars/carschoose.cpp

HEADERS  += mainwindow.h \
    Settings/settings.h \
    Settings/settings_gui.h \
    Catalogs/Cars/carslist.h \
    allinclude.h \
    Catalogs/Cars/carschoose.h
