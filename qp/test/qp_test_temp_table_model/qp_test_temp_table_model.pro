
QT       += core gui sql network svg

TARGET = QpSqlTableModel_test
TEMPLATE = app

CONFIG +=  windows
#CONFIG +=  console

#DEFINES += QT_NO_SPINBOX

OBJECTS_DIR     = obj
RCC_DIR         = rcc
UI_DIR          = ui
DESTDIR         = bin

TRANSLATIONS +=  ../db/view/QtLangPblTableView_en.ts ../db/view/QtLangPblTableView_ru.ts ../db/view/QtLangPblTableView_zh.ts

CODECFORTR      = UTF-8
CODECFORSRC     = UTF-8

include( $$PWD/../../config/general/general.pri)  # До INCLUDEPATH +=

INCLUDEPATH += $$PWD

INCLUDEPATH += ../
DEPENDPATH  += ../
INCLUDEPATH += ../../
DEPENDPATH  += ../../


INCLUDEPATH += ../qp
DEPENDPATH  += ../qp

include( $$include2( $$PWD/../../config/general/general.pri))  # До INCLUDEPATH +=

include( $$include2( $$PWD/../../my_lib/logging_system/logging_system.pri))

include( $$include2( $$PWD/../core/qp_core.pri))
#include( $$include2( $$PWD/../config/lib_qp_core.pri))

include( $$include2( $$PWD/../gui/qp_gui.pri))
#include( $$include2( $$PWD/../config/lib_qp_gui.pri))

#include( $$include2( ../ntw/qp_ntw.pri))

#include( $$include2( $$PWD/../sql/qp_sql.pri))
include( $$include2( $$PWD/../config/lib_qp_sql.pri))

include( $$include2( $$PWD/../delegates/qp_delegates.pri))


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
    qp_sqltablemodel2.cpp \
    config2.cpp \
    dialog_test.cpp \
    db1.cpp \
    app_def.cpp

HEADERS  += \
    config.h \
    version_app.h \
    qp_sqltablemodel2.h \
    config2.h \
    dialog_test.h \
    db1.h \
    app_def.h

FORMS    += dialog.ui


OTHER_FILES += \
    rc2.rc

win32 {
  RC_FILE     += rc2.rc
}

PWD_WIN = $${PWD}/../db/view
DESTDIR_WIN = $${OUT_PWD}/$${DESTDIR}

PWD_WIN ~= s,/,\\,g
DESTDIR_WIN ~= s,/,\\,g

# dont remember to make Tool/External/QtLinguist/Update Translations (lupdate) and Update Translations (lrelease) !
copyfiles.commands = $$quote(cmd /c xcopy /S /I /Y $$PWD_WIN\\*.qm $$DESTDIR_WIN)
QMAKE_EXTRA_TARGETS += copyfiles
PRE_TARGETDEPS += copyfiles
message(copyfiles.commands $$copyfiles.commands)
