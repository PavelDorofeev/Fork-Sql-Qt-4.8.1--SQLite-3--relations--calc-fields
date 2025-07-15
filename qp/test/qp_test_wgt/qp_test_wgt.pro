#-------------------------------------------------
#
# Project created by QtCreator 2025-05-06T19:31:49
#
#-------------------------------------------------

QT       += core gui

TARGET = qp_test_wgt
TEMPLATE = app

OBJECTS_DIR     = obj
MOC_DIR         = moc
RCC_DIR         = rcc
UI_DIR          = ui

include($$PWD/../../config/general/general.pri)

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/../

include($$PWD/../../config/lib_qp.pri)



SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui
