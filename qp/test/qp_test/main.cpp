#include <QtGui/QApplication>

#include "dialog.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    QCoreApplication::setOrganizationName( reestrDef::REESTR_ORGANIZATION_NAME);
//    QCoreApplication::setApplicationName( reestrDef::REESTR_APPLICATION_NAME);



//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    //fakeSrvAnsw::emulateSrvAnswer( "D:\\DEVELOPMENT\\QT4\\_MY__\\config\\general\\srv_answ_data.txt");


    Dialog dlg;
    dlg.show();
//    Atol_Kkt_Wgt_Com *wgt = new Atol_Kkt_Wgt_Com( QVariantMap() ) ;

//    wgt->showMaximized();

    return a.exec();
}
