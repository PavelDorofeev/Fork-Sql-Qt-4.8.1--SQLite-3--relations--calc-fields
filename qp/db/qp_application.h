#ifndef QP_APPLICATION_H
#define QP_APPLICATION_H

#include <QApplication>
#include <QTranslator>
#include <QIcon>

class QpApplication : public QApplication
{
    Q_OBJECT
public:
    QpApplication(int &argc, char **argv, int flags= ApplicationFlags);

    QTranslator qtLanguageTranslator;

    QString langId;

    bool notify(QObject *obj, QEvent *evt);
signals:
    
public slots:
    bool slot_change_language(QString name);

};

#endif // QP_APPLICATION_H
