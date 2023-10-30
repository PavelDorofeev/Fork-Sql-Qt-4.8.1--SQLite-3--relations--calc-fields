#-------------------------------------------------
#
# Project created by QtCreator 2022-11-27T15:52:34
#
#-------------------------------------------------

QT       += core gui sql network svg

TARGET = pbltableview_test
TEMPLATE = app

CONFIG +=  console windows

#DEFINES += QT_NO_SPINBOX

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


CONFIG(release,release|debug){

    contains(CONFIG,static){

        DEFINES +=STATIC_MODE
        QTPLUGIN += qsvg

        message("----- RELEASE STATIC ----")
    }
    else{

        message("----- release  shared ----??????")
    }
}
else:CONFIG(debug,release|debug){
    # DEBUG

    contains(CONFIG,static){
        message("????????---------- debug static -----------??????????")

    }
    else:contains(CONFIG,shared){
        message("---------- DEBUG SHARED ----------- ")

    }
}



SOURCES +=\
    main.cpp \
    config.cpp \
    pblsqlrelationaltablemodel2.cpp \
    config2.cpp \
    dialog_test.cpp

HEADERS  += \
    config.h \
    version_app.h \
    pblsqlrelationaltablemodel2.h \
    config2.h \
    dialog_test.h \
    ../common/my_prog.h

FORMS    += dialog.ui

RESOURCES += \
    pbltableview/resource2.qrc

OTHER_FILES += \
    rc2.rc \
    ../common/common-for-pbltableview.pri

win32 {
  RC_FILE     += rc2.rc
}

PWD_WIN = $${PWD}/../pbltableview
DESTDIR_WIN = $${OUT_PWD}/$${DESTDIR}

PWD_WIN ~= s,/,\\,g
DESTDIR_WIN ~= s,/,\\,g

# dont remember to make Tool/External/QtLinguist/Update Translations (lupdate) and Update Translations (lrelease) !
copyfiles.commands = $$quote(cmd /c xcopy /S /I /Y $$PWD_WIN\\*.qm $$DESTDIR_WIN)
QMAKE_EXTRA_TARGETS += copyfiles
PRE_TARGETDEPS += copyfiles
message(copyfiles.commands $$copyfiles.commands)
