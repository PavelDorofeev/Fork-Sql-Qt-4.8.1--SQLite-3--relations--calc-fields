#-------------------------------------------------
#
# Project created by QtCreator 2022-11-27T15:52:34
#
#-------------------------------------------------

QT       += core gui sql network

TARGET = pbltableview_test
TEMPLATE = app

CONFIG +=  console windows

OBJECTS_DIR     = tmp\\obj\\$$out_dir
MOC_DIR         = tmp\\moc\\$$out_dir
RCC_DIR         = tmp\\rcc\\$$out_dir
UI_DIR          = ui
DESTDIR         = bin

TRANSLATIONS +=  ../pbltableview/QtLangPblTableView_en.ts ../pbltableview/QtLangPblTableView_ru.ts ../pbltableview/QtLangPblTableView_zh.ts

CODECFORTR      = UTF-8
CODECFORSRC     = UTF-8

INCLUDEPATH += $$PWD

INCLUDEPATH += ../
DEPENDPATH  += ../

INCLUDEPATH += ../pbltableview
DEPENDPATH  += ../pbltableview

include(../pbltableview/pbltableview.pri)

include(../logging_system/logging_system.pri)


SOURCES +=\
    main.cpp \
    dialog.cpp \
    config.cpp \
    pblsqlrelationaltablemodel2.cpp \
    ../my_gui/msg.cpp \
    config2.cpp

HEADERS  += \
    dialog.h \
    config.h \
    version.h \
    pblsqlrelationaltablemodel2.h \
    ../my_gui/msg.h \
    config2.h

FORMS    += dialog.ui \
    ../my_gui/msg.ui

RESOURCES += \
    pbltableview/resource2.qrc

OTHER_FILES += \
    rc2.rc

win32 {
  RC_FILE     += rc2.rc
}

PWD_WIN = $${PWD}/../pbltableview
DESTDIR_WIN = $${OUT_PWD}/$${DESTDIR}

PWD_WIN ~= s,/,\\,g
DESTDIR_WIN ~= s,/,\\,g

# dont remember to make Tool/External/QtLinguist/Update Translations (lupdate) and Update Translations (lrelease) !
copyfiles.commands = $$quote(cmd /c xcopy /S /I /Y $$PWD_WIN\*.qm $$DESTDIR_WIN)
QMAKE_EXTRA_TARGETS += copyfiles
PRE_TARGETDEPS += copyfiles
message(copyfiles.commands $$copyfiles.commands)
