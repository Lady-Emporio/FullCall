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
    Catalogs/Cars/carschoose.cpp \
    Catalogs/Colors/colors.cpp \
    Catalogs/Cars_colors/carscolors.cpp \
    Catalogs/BaseTable/basetable.cpp \
    Catalogs/Managers/managers.cpp \
    Catalogs/Dealers/dealers.cpp

HEADERS  += mainwindow.h \
    Settings/settings.h \
    Settings/settings_gui.h \
    Catalogs/Cars/carslist.h \
    allinclude.h \
    Catalogs/Cars/carschoose.h \
    Catalogs/Colors/colors.h \
    Catalogs/Cars_colors/carscolors.h \
    Catalogs/BaseTable/basetable.h \
    Catalogs/Managers/managers.h \
    Catalogs/Dealers/dealers.h
