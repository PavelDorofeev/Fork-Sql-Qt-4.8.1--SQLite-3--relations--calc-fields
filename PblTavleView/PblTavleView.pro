#-------------------------------------------------
#
# Project created by QtCreator 2022-11-27T15:52:34
#
#-------------------------------------------------

QT       += core gui sql

TARGET = PblTavleView
TEMPLATE = app

CONFIG +=  console windows

OBJECTS_DIR     = tmp\\obj\\$$out_dir
MOC_DIR         = tmp\\moc\\$$out_dir
RCC_DIR         = tmp\\rcc\\$$out_dir
UI_DIR          = ui

INCLUDEPATH += ../../my_lib
DEPENDPATH += ../../my_lib

INCLUDEPATH += ../


include(../../my_lib/logging_system/logging_system.pri)


SOURCES += main.cpp\
        dialog.cpp \
    pbltableview.cpp \
    btntoolbox.cpp \
    some_tests.cpp \
    table_dlg.cpp \
    search_settings_dlg.h.cpp \
    pbltableview_purchases.cpp

HEADERS  += dialog.h \
    pbltableview.h \
    btntoolbox.h \
    some_tests.h \
    table_dlg.h \
    search_settings_dlg.h \
    pbltableview_purchases.h

FORMS    += dialog.ui \
    find_dlg.ui \
    btntoolbox.ui \
    table_dlg.ui

RESOURCES += \
    rrr.qrc
