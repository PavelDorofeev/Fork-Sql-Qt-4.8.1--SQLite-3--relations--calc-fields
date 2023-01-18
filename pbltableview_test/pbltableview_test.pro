#-------------------------------------------------
#
# Project created by QtCreator 2022-11-27T15:52:34
#
#-------------------------------------------------

QT       += core gui sql

TARGET = pbltableview_test
TEMPLATE = app

CONFIG +=  console windows

OBJECTS_DIR     = tmp\\obj\\$$out_dir
MOC_DIR         = tmp\\moc\\$$out_dir
RCC_DIR         = tmp\\rcc\\$$out_dir
UI_DIR          = ui
DESTDIR         = bin

#TRANSLATIONS +=  QtLanguage_en.ts QtLanguage_ru.ts QtLanguage_zh.ts

#CODECFORTR      = UTF-8
#CODECFORSRC     = UTF-8

INCLUDEPATH += $$PWD

INCLUDEPATH += ../
DEPENDPATH  += ../

include(../pbltableview/pbltableview.pri)

include(../logging_system/logging_system.pri)


SOURCES +=\
    main.cpp \
    dialog.cpp \
    pblsqlrelationaltablemodel_purchases.cpp \
    config.cpp

HEADERS  += \
    dialog.h \
    pblsqlrelationaltablemodel_purchases.h \
    config.h

FORMS    += dialog.ui

RESOURCES += \
    pbltableview/resource2.qrc

OTHER_FILES += \
    rc2.rc

win32 {
  RC_FILE     += rc2.rc
}

PWD_WIN = $${PWD}
DESTDIR_WIN = $${OUT_PWD}/bin

PWD_WIN ~= s,/,\\,g
DESTDIR_WIN ~= s,/,\\,g

#copyfiles.commands = $$quote(cmd /c xcopy /S /I /Y $$PWD_WIN\*.qm $$DESTDIR_WIN)
#QMAKE_EXTRA_TARGETS += copyfiles
#PRE_TARGETDEPS += copyfiles
#message(copyfiles.commands $$copyfiles.commands)
