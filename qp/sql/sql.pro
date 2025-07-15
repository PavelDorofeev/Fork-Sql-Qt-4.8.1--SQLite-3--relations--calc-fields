TEMPLATE = lib

QT = core gui sql svg

CONFIG += ordered

OBJECTS_DIR = tmp\obj
MOC_DIR = tmp\moc
RCC_DIR = tmp\rcc
UI_DIR = tmp\ui

include( $$PWD/../../config/general/general.pri )


INCLUDEPATH += $$includePath( $$PWD )
INCLUDEPATH += $$includePath( $$PWD/../ )
INCLUDEPATH += $$includePath( $$PWD/../../ )
#DEPENDPATH += $$dependPath( $$PWD )

INCLUDEPATH += $$includePath( $$PWD/../ ) #include qp/meta/... для этого, чтобы включения находились (в *.h)
#DEPENDPATH += $$dependPath( $$PWD/../ )

#error( $$PWD )

include( $$include2( $$PWD/../config/lib_qp_core.pri ) )
include( $$include2( $$PWD/../config/lib_qp_gui.pri ) )
include( $$include2( $$PWD/../config/lib_qp_ntw.pri ) )



include( $$include2( $$PWD/tableview/qp_tableview.pri ) )
include( $$include2( $$PWD/model/qp_model.pri ) )
include( $$include2( $$PWD/view/qp_view.pri ) )

include( $$include2( $$PWD/../config/create_lib_qp_sql.pri ) )

include( $$include2( $$PWD/qp_sql.pri ) )
