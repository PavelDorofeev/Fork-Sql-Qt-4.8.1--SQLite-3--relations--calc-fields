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
DESTDIR         = bin

TRANSLATIONS +=  QtLanguage_en.ts QtLanguage_ru.ts QtLanguage_zh.ts

CODECFORTR      = UTF-8
CODECFORSRC     = UTF-8

include(../sql_pbl/sql_pbl.pri)

INCLUDEPATH += ../../my_lib
DEPENDPATH += ../../my_lib

INCLUDEPATH += ../sql_pbl

INCLUDEPATH += ../


include(../logging_system/logging_system.pri)


SOURCES += main.cpp\
        dialog.cpp \
    pbltableview.cpp \
    some_tests.cpp \
    table_dlg.cpp \
    search_settings_dlg.cpp \
    btn_toolbox.cpp \
    pblapplication.cpp \
    pblsqlrelationaltablemodel_purchases.cpp \
    doubledelegate.cpp \
    my_sql.cpp

HEADERS  += dialog.h \
    pbltableview.h \
    some_tests.h \
    table_dlg.h \
    search_settings_dlg.h \
    btn_toolbox.h \
    pblapplication.h \
    pblsqlrelationaltablemodel_purchases.h \
    doubledelegate.h \
    my_sql.h

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

#QMAKE_EXTRA_TARGETS += QtLanguage
#PRE_TARGETDEPS += QtLanguage
#QtLanguage.commands =  $$PWD/QtLanguage_

PWD_WIN = $${PWD}
DESTDIR_WIN = $${OUT_PWD}/bin

PWD_WIN ~= s,/,\\,g
DESTDIR_WIN ~= s,/,\\,g

copyfiles.commands = $$quote(cmd /c xcopy /S /I /Y $$PWD_WIN\*.qm $$DESTDIR_WIN)
#copyfiles.commands = $$PWD/qt_language.bat
QMAKE_EXTRA_TARGETS += copyfiles
PRE_TARGETDEPS += copyfiles
message(copyfiles.commands $$copyfiles.commands)
