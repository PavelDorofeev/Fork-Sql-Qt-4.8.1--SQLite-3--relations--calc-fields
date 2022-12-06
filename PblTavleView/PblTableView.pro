#-------------------------------------------------
#
# Project created by QtCreator 2022-11-27T15:52:34
#
#-------------------------------------------------

QT       += core gui sql

TARGET = PblTableView
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
    some_tests.cpp \
    table_dlg.cpp \
    pbltableview_purchases.cpp \
    search_settings_dlg.cpp \
    btn_toolbox.cpp

HEADERS  += dialog.h \
    pbltableview.h \
    some_tests.h \
    table_dlg.h \
    search_settings_dlg.h \
    pbltableview_purchases.h \
    btn_toolbox.h

FORMS    += dialog.ui \
    table_dlg.ui \
    search_settings_dlg.ui \
    btn_toolbox.ui

RESOURCES += \
    resource2.qrc

OTHER_FILES += \
    rc2.rc

win32 {
  RC_FILE     += rc2.rc
}
