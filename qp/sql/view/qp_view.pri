#include( $$PWD/../../../qp/qp_delegates/delegates.pri)


HEADERS += \
    $$PWD/search_settings_dlg.h \
    $$PWD/btn_toolbox.h \
    $$PWD/buttoniconautoresize.h \
    $$PWD/horizontal_header.h \
    $$PWD/qp_tableview_wrapper.h \
    $$PWD/qp_table_dlg.h \
    $$PWD/qp_tableview_wrapper2.h \
    $$PWD/vertical_header.h \

SOURCES += \
    $$PWD/btn_toolbox.cpp \
    $$PWD/search_settings_dlg.cpp \
    $$PWD/buttoniconautoresize.cpp \
    $$PWD/horizontal_header.cpp \
    $$PWD/qp_tableview_wrapper.cpp \
    $$PWD/qp_table_dlg.cpp \
    $$PWD/qp_tableview_wrapper2.cpp \
    $$PWD/vertical_header.cpp \

FORMS    += \
    $$PWD/btn_toolbox.ui \
    $$PWD/search_settings_dlg.ui \
    $$PWD/qp_table_dlg.ui

RESOURCES += \
    $$PWD/qp_sql.qrc
