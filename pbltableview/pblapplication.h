#ifndef PBLAPPLICATION_H
#define PBLAPPLICATION_H

#include <QApplication>
#include <QTranslator>
#include <QIcon>

class PblApplication : public QApplication
{
    Q_OBJECT
public:
    PblApplication(int &argc, char **argv, int flags= ApplicationFlags);

    QTranslator qtLanguageTranslator;

    QString langId;

signals:
    
public slots:
    bool slot_change_language(QString name);

};

#endif // PBLAPPLICATION_H
