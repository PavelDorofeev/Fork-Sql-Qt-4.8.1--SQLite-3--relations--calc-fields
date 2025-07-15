#ifndef QP_APPLICATION_H
#define QP_APPLICATION_H

#include <QApplication>
#include <QTranslator>
#include <QIcon>

#include "qp/gui/dll_qp_gui_global.h"

class LIB_PREFIX_QP_GUI QpApplication : public QApplication
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
    void about_to_quit();
    void slot_msg();
    void slot_lastWindowClosed();

};

#endif // QP_APPLICATION_H
