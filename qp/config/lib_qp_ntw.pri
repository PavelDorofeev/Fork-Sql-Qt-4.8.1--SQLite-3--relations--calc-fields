INCLUDEPATH += $$includePath( $$PWD/../)
INCLUDEPATH += $$includePath( $$PWD/../../)

CONFIG(release,release|debug){

    contains(CONFIG,static){
        # ----------------------------------------------
            LIBS += -L$$PWD/../ntw/release -lntw
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


        DEFINES += $$fromfile( $$PWD/cfg_qp_debug.pri , DEFINES_LIBS_USING_QP_NTW)
        DEFINES -= $$fromfile( $$PWD/cfg_qp_debug.pri , DEFINES_LIB_IS_EXPORTED_QP_NTW)

        # ----------------------------------------------
            LIBS += -L$$PWD/../ntw/debug -lntw
        # ----------------------------------------------
        ##error($$DEFINES)

    }
}
