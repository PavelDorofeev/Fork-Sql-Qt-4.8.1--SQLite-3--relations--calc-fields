#include <QtGui/QApplication>
#include "dialog.h"

#include "qp/core/qp_core.h"
#include "qp/core/meta/meta.h"
#include "qp/core/qp_core.h"
#include "qp/core/file/qp_fileinfo.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog dlg;
    dlg.show();
    
    //qp::meta::cnct( dlg , SIGNAL( close() ) , dlg , SLOT( qui));

    qp::file::DLL_ARCH dd = qp::file::DLL_ARCH_X64;

    qDebug() << dd;
    return a.exec();
}
