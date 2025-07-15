TEMPLATE = app

TARGET = test_qp

QT += core gui

CONFIG += ordered

OBJECTS_DIR     = obj
MOC_DIR         = moc
RCC_DIR         = rcc
UI_DIR          = ui

include($$PWD/../../config/general/general.pri)


INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/../

include($$PWD/../config/lib_qp.pri)


#include( $$include2( $$PWD/../config/create_lib_my_lib.pri) )

SOURCES += \
    main.cpp \
    dialog.cpp

HEADERS += \
    dialog.h

FORMS += \
    dialog.ui







