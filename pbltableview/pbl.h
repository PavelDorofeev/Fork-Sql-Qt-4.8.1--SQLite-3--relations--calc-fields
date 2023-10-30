#ifndef PBL_H
#define PBL_H

#include <QString>
#include <QWidget>


class pbl
{
public:

    enum SOME_FIELDS_VAL
    {
        UNDEFINED = -1 ,

        COL_UNDEFINED = UNDEFINED,
        ROW_UNDEFINED = UNDEFINED,
        INT_UNDEFINED = UNDEFINED,

        REL_UNDEFINED = 0,

        REL_EMPTY_ID  = REL_UNDEFINED,
        EMPTY_ID      = REL_UNDEFINED,
    };


    pbl();

    //static Msg2* getMsg2(QWidget *parent=0);

    static QString toStr_Event_Type(int event);

    static QString toStr_ItemFlag(int ItemFlag);

    static const QString toStr_InputMethodQuery(Qt::InputMethodQuery mtd);


#ifdef THIS_IS_STATIC

#define _CONNECT_(AA,BB,CC,DD) if(!connect(AA,BB,CC,DD)){\
    qCritical() << "!!!! Error connect(..) signal : " << BB << " / slot : " << DD;\
}

#define _DISCONNECT_(AA,BB,CC,DD) if(!connect(AA,BB,CC,DD)){\
    qCritical() << "!!!! Error dis-connect(..) signal : " << BB << " / slot : " << DD;\
}

#else

#define _CONNECT_(AA,BB,CC,DD) \
if( ! connect ( AA , BB , CC ,DD )){\
    qCritical() << "!!!! Error connect(..) signal : " << BB << " / slot : " << DD;\
    pbl::message2(0 , QString("Error connect(..) ") , AA->objectName()+"\n\t"+QString(BB), CC->objectName()+"\n\t"+QString(DD));\
    qCritical() << "    " << AA->objectName();\
}

#define _DISCONNECT_(AA,BB,CC,DD) \
if(!disconnect(AA,BB,CC,DD)){\
    qCritical() << "!!!! Error dis-connect(..) signal : " << BB << " / slot : " << DD;\
    pbl::message2(0,"Error in function dis-connect(..)" , BB, DD);\
}

#endif

static void message2(QWidget *parent,
             QString header ,
             QString signal ,
             QString slot);
};

#endif // PBL_H
