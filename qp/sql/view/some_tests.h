#ifndef MY_OBJECTS_H
#define MY_OBJECTS_H

#include <QWidget>
#include <QMessageBox>


//#ifdef THIS_IS_STATIC

//#define _CONNECT_(AA,BB,CC,DD) if(!connect(AA,BB,CC,DD)){\
//    qCritical() << "!!!! Error connect(..) signal : " << BB << " / slot : " << DD;\
//}

//#define _DISCONNECT_(AA,BB,CC,DD) if(!connect(AA,BB,CC,DD)){\
//    qCritical() << "!!!! Error dis-connect(..) signal : " << BB << " / slot : " << DD;\
//}

//#else

//#define _CONNECT_(AA,BB,CC,DD) \
//if( ! connect ( AA , BB , CC ,DD )){\
//    qCritical() << "!!!! Error connect(..) \n\t" << AA->objectName() << " signal : " << BB << " \n\t slot :  "<< CC->objectName() << " " << DD;\
//    QMessageBox::warning(0 , "Error connect ", QString("Error connect(..) \n\tsignal: ") + " " + QString(BB)+"    objectName:"+AA->objectName()+"\n\tslot:     "+ QString(DD) + " objectName:    " + CC->objectName());\
//}

//#define _DISCONNECT_(AA,BB,CC,DD) \
//if(!disconnect(AA,BB,CC,DD)){\
//    qCritical() << "!!!! Error dis-connect(..) signal : " << BB << " / slot : " << DD;\
//    QMessageBox::warning(0,"Error in function dis-connect(..)" , BB, DD);\
//}

//#endif

#endif //MY_OBJECTS_H
