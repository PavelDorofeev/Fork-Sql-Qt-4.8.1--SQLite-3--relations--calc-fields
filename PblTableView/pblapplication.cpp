#include "pblapplication.h"
#include <QMessageBox>

PblApplication::PblApplication(int &argc, char **argvs, int flags) :
    QApplication(argc, argvs, flags),
    langId(QString())
{


}

bool PblApplication::slot_change_language(QString name)
{

    if( qtLanguageTranslator.load(QString("QtLanguage_") + name))
    {
        //QMessageBox::critical(0, mySql::error , QObject::tr("loading language '%1' succesfull").arg(name));
        langId = name;
    }
    else
    {
        //QMessageBox::critical(0, mySql::error , QObject::tr("loading language '%1' unsuccesfull, but it will be working normal").arg(name));
        langId = name;
        //return false;
    }

    installTranslator(&qtLanguageTranslator);

    return true;

}
