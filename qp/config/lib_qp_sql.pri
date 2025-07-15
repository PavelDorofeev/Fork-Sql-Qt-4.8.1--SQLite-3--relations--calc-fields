INCLUDEPATH += $$includePath( $$PWD/../)

CONFIG(release,release|debug){

    contains(CONFIG,static){
        # ----------------------------------------------
            LIBS += -L$$PWD/../sql/release -lsql
        # ----------------------------------------------

    }
    else{
        #error(6597589789506870948609)
    }
}
else:CONFIG(debug,release|debug){

    contains(CONFIG,static){
        #error(648498954546463465)
    }
    else:contains(CONFIG,shared){

        # ----------------------------------------------
            LIBS += -L$$PWD/../sql/debug -lsql
        # ----------------------------------------------

        DEFINES += $$fromfile( $$PWD/cfg_qp_debug.pri , DEFINES_LIBS_USING_QP_SQL)
        DEFINES -= $$fromfile( $$PWD/cfg_qp_debug.pri , DEFINES_LIB_IS_EXPORTED_QP_SQL)

        ##error($$DEFINES)

    }
}
