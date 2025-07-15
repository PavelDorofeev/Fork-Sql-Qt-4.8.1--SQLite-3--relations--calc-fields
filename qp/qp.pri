INCLUDEPATH += $$includePath($$PWD)
INCLUDEPATH += $$includePath($$PWD/../)

include($$PWD/tableview/qp_tableview.pri)

include($$PWD/core/qp_core.pri)
include($$PWD/gui/qp_gui.pri)
include($$PWD/ntw/qp_ntw.pri)
include($$PWD/sql/qp_sql.pri)

#include($$PWD/meta/qp_meta.pri)
#include($$PWD/gui/qp_gui.pri)
#include($$PWD/dbg/qp_dbg.pri)
#include($$PWD/db/qp_db.pri)
#include($$PWD/db/model/qp_model.pri)
#include($$PWD/db/view/qp_view.pri)
#include($$PWD/ntw/qp_ntw.pri)
#include($$PWD/evt/qp_evt.pri)
#include($$PWD/cont/qp_cont.pri)
#include($$PWD/delegates/qp_delegates.pri)
#include($$PWD/file/qp_file.pri)

#HEADERS += \
#    $$PWD/dll_qp_global.h

