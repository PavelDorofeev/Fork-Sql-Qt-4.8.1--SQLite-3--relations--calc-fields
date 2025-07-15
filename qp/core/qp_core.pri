INCLUDEPATH += $$includePath($$PWD)
INCLUDEPATH += $$includePath($$PWD/../)

include($$PWD/meta/qp_meta.pri)
include($$PWD/dbg/qp_dbg_core.pri)
include($$PWD/evt/qp_evt.pri)
include($$PWD/cont/qp_cont.pri)
include($$PWD/file/qp_file.pri)
include($$PWD/logging_system/logging_system.pri)
include($$PWD/json/json.pri)

HEADERS += \
    $$PWD/dll_qp_core_global.h

