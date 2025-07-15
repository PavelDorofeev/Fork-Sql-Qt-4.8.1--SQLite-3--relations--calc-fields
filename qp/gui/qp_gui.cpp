#include "qp_gui.h"

#include <QApplication>
#include <QDesktopWidget>

#include "qp/gui/smart_process_dlg.h"

namespace qp
{

namespace gui
{

QString styleToHtmlAttr(int styles)
{
    if(styles & LOG_STYLE_SEND )
        return "color:#0000cd;"; // BLUE

    else if(styles & LOG_STYLE_SEND2 )
        return "color:#55305a;"; // magenta

    else if(styles & LOG_STYLE_RECEIVE )
        return "color:green;"; // green #00cd00

    else if(styles & LOG_STYLE_RECEIVE2 )
        return "color:brown;";

    else if(styles & LOG_STYLE_ERROR )
        return "color:#cd0000;"; // red

    else if(styles & LOG_STYLE_ERROR2 )
        return "color:#ab0000;"; // red

    else if(styles & LOG_STYLE_PLAINTEXT )
        return "color:#bbbbbb;"; // dark gray

    else if(styles & LOG_STYLE_CODE_PRE )
        return "color:#aaaaaa;"; // dark gray

    else

        return "color:gray;";


}


bool call_slot( QWidget *parent,
                const QObject * slotOwner,
                const QString &hdr,
                const QString &txt1,
                const QString &txt2,
                const QString &slot_name ,
                const QList<const QObject*> &ObjLst,
                const QList<QVariant>& pars,
                QVariant &retVal,
                bool closeWindowOnFinished,
                bool silent
                )
{

    // ---------------------------------------------------------------------------
    //
    //                        ВНИАМНИЕ!
    //
    // заметьте ,что у слотов обязательно должен возвращаться параметр QVariant()
    //
    //
    // ----------------------------------------------------------------------------


    // ----------------------------------------------------------------------------
    //              НОPМАЛЬНО КОГДА:
    //
    //      ConnectOfd это какой-то ваш тип от (QObject)
    //      typeid("ConnectOfd").name() возвращает char const [xx]  (xx = 11 у нас)
    //      QMetaType::type("ConnectOfd") возвращает 0
    //      сделать регистрацию в метасистеме qRegisterMetaType<ConnectOfd>("ConnectOfd");
    //          не удается, ошибка компиляции
    // ----------------------------------------------------------------------------

    Smart_Process_Dlg * dlg = new Smart_Process_Dlg( parent ,

                                                     slotOwner ,

                                                     hdr,

                                                     txt1,

                                                     txt2,

                                                     slot_name,

                                                     ObjLst,

                                                     pars,

                                                     closeWindowOnFinished,

                                                     silent


                                                     );


    dlg->setModal( false );

    dlg->show();

    if ( dlg->exec() == QDialog::Rejected ) //
        ;

    retVal = dlg->getRetValue();

    bool res = dlg->getInvokeMethodResult();

    delete dlg;

    QApplication::setOverrideCursor( Qt::ArrowCursor );

    return res;

}


void setWindow_woTitle(QWidget * wgt)
{
    Qt::WindowFlags flags = wgt->windowFlags();

    flags &= ( ~Qt::WindowTitleHint );

    wgt->setWindowFlags( flags );

    //qDebug() << "flags setWindow_woTitle " << flags;
}

void setWindow_woFrame_and_woTiltle(QWidget * wgt)
{
    Qt::WindowFlags flags = wgt->windowFlags();

    // -------------------------------------------
    // убирает рамку вокруг окна
    // -------------------------------------------
    flags |= Qt::FramelessWindowHint;

    wgt->setWindowFlags( flags );

    //qDebug() << "flags setWindow_woFrame " << flags;
}

void setWindow_woToolsBtn(QWidget * wgt)
{
    Qt::WindowFlags flags = wgt->windowFlags();

    flags |= Qt::WindowMinMaxButtonsHint
            | Qt::WindowCloseButtonHint;

    wgt->setWindowFlags( flags );

    //qDebug() << "flags setWindow_woToolsBtn " << flags;
}

void setWindow_woTitle__woFrame_woToolsBtn(QWidget * wgt)
{
    setWindow_woToolsBtn(wgt);
    setWindow_woFrame_and_woTiltle(wgt);
    setWindow_woTitle(wgt); //!! after

    //qDebug() << "flags setWindow_woTitle__woFrame_woToolsBtn  " << wgt->windowFlags();
}

void setWindow_woTitle__woFrame_woToolsBtn2(QWidget * wgt)
{
    Qt::WindowFlags flags = wgt->windowFlags();

    flags &= ( ~Qt::WindowTitleHint );

    flags |= (Qt::FramelessWindowHint
              | Qt::WindowMaximizeButtonHint
              | Qt::WindowCloseButtonHint);

    wgt->setWindowFlags( flags );

    //qDebug() << "flags setWindow_woTitle__woFrame_woToolsBtn2 " << wgt->windowFlags();
}

void setWindow_restore (QWidget * wgt)
{
    Qt::WindowFlags flags = wgt->windowFlags();

    flags |= ( Qt::WindowTitleHint );

    flags &= (~Qt::FramelessWindowHint);
    flags &= (~Qt::WindowMaximizeButtonHint);
    flags &= (~Qt::WindowCloseButtonHint);

    wgt->setWindowFlags( flags );

    //qDebug() << "flags setWindow_woTitle__woFrame_woToolsBtn2 " << wgt->windowFlags();
}

void set_window_rounded_wo_title( QWidget  *wgt)
{
    wgt->setAttribute(Qt::WA_TranslucentBackground);

    qp::gui::setWindow_woTitle__woFrame_woToolsBtn( wgt );


}
void center_window( QWidget  *wgt)
{
    QSize sz = screen_size();

    int x =0 ;

    if( sz.width() > wgt->width())
        x = ( sz.width() - wgt->width() ) /2 ;
    else
        x = wgt->x();

    int y = 0;

    if( sz.height() > wgt->height())
        y = ( sz.height() - wgt->height() ) /2 ;
    else
        y = wgt->y();


    wgt->move(  x , y );


}


QSize screen_size( )
{
    QDesktopWidget *dWgt = QApplication::desktop();

    //    qDebug() << "dWgt->height()" << dWgt->height();
    //    qDebug() << "physicalDpiX:" << dWgt->physicalDpiX();
    //    qDebug() << "logicalDpiX:" << dWgt->logicalDpiX();
    //    qDebug() << "physicalDpiY:" << dWgt->physicalDpiY();
    //    qDebug() << "logicalDpiY:" << dWgt->logicalDpiY();
    //    qDebug() << "heightMM:" << dWgt->heightMM();
    //    qDebug() << "screenGeometry:" <<dWgt->screenGeometry();

    //    qDebug() << "1pt:" << (double)dWgt->height() <<"см ";
    //    qDebug() << "1pt:" << (double)pointSize *25.4/72 <<"см ";

    QSize sz ( dWgt->width() , dWgt->height() );

    return sz
            ;
}


}

}
