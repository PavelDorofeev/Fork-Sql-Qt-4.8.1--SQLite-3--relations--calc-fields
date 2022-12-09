#include "pblapplication.h"
#include <QMessageBox>

PblApplication::PblApplication(int &argc, char **argvs, int flags) :
    QApplication(argc, argvs, flags),
    langId(QString())
{

    //qtLanguageTranslator.load(QString("QtLanguage_") + QString("ru"));
    //qtLanguageTranslator.load(QString("QtLanguage_") + QString("en_Uk"));
    //installTranslator(&qtLanguageTranslator);
}

bool PblApplication::slot_change_language(QString name)
{

    //qtLanguageTranslator.
    if( qtLanguageTranslator.load(QString("QtLanguage_") + name))
    {
        //QMessageBox::critical(0, QObject::tr("error") , QObject::tr("loading language '%1' succesfull").arg(name));
        langId = name;
    }
    else
    {
        //QMessageBox::critical(0, QObject::tr("error") , QObject::tr("loading language '%1' unsuccesfull, but it will be working normal").arg(name));
        langId = name;
        //return false;
    }

    installTranslator(&qtLanguageTranslator);

    return true;

}
