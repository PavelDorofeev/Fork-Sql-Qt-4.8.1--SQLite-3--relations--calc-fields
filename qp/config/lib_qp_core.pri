INCLUDEPATH += $$includePath($$PWD/../)

CONFIG(release,release|debug){

    contains(CONFIG,static){
        # ----------------------------------------------
            LIBS += -L$$PWD/../core/release -lcore
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
            LIBS += -L$$PWD/../core/debug -lcore
        # ----------------------------------------------

        DEFINES += $$fromfile( $$PWD/cfg_qp_debug.pri , DEFINES_LIBS_USING_QP_CORE)
        DEFINES -= $$fromfile( $$PWD/cfg_qp_debug.pri , DEFINES_LIB_IS_EXPORTED_QP_CORE)

        ##error($$DEFINES)

    }
}
