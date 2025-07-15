#include "sizerememberdlg.h"

#include <QDebug>
#include <QApplication>
#include <QMessageBox>
#include <QResizeEvent>

SizeRememberDlg::SizeRememberDlg( QWidget *parent )
    :
    QDialog(parent),

    reestTreeName(QCoreApplication::organizationName()),
    reestrName(QCoreApplication::applicationName()),
    resizeStoreEnabled( false ),
    changedSize(QSize()),
    changedPos(QPoint()),
    pathRect(QString()),
    pathPos(QString())

{
    /*

     ВАЖНО : В КОНСТPУКТОPЕ НЕ ВЫЗЫВАЮТСЯ ВИPТУАЛЬЬНЫЕ ФУНКЦИИ
     поэтому init()
     */


    if( QCoreApplication::organizationName().isEmpty() || QCoreApplication::applicationName().isEmpty())
    {
        QMessageBox::warning( this ,
                              QString::fromUtf8("внимание"),
                              QString::fromUtf8("не инициализированы QApplication::organizationName() или QApplication::applicationName(), сохранение размеров окна не будет работать")

                              );
    }
    else
    {
        resizeStoreEnabled = true;
    }

//    qDebug() << "SizeRememberDlg pathRect:"<<pathRect;
//    qDebug() << "                pathPos:"<<pathPos;

}

void SizeRememberDlg::init()
{
    /*

     ВАЖНО : В КОНСТPУКТОPЕ НЕ ВЫЗЫВАЮТСЯ ВИPТУАЛЬНЫЕ ФУНКЦИИ
        поэтому init()
     */

    pathRect = "/sizes/"+getReestrPrefix()+"/"+reestrName+"_rect";
    pathPos = "/sizes/"+getReestrPrefix()+"/"+reestrName+"_position";

}


void SizeRememberDlg::closeEvent(QCloseEvent *evt)
{
    //qDebug() << "closeEvent changedSize:"  << changedSize << " changedPos :"<< changedPos;

    saveSizeAndPosToReestr( changedSize , changedPos );

    QDialog::closeEvent(evt);
}

void SizeRememberDlg::showEvent(QShowEvent *evt)
{
    //qDebug() << "showEvent changedSize:"  << changedSize << " changedPos :"<< changedPos;

    /*                      ВНИМНИЕ!
      глобальный setStyleSheet для QDialog устанавливает здесь мин размер
      НЕ СМОТPЯ на ui наследника
      т.о. в ui наследника переустнавливается minimumSize
      тким образом надо в конструкторе наследника (он позже вызвается) делать свой setStyleSheet
    */


    restoreFromReestr();

    QDialog::showEvent(evt);
}

void SizeRememberDlg::resizeEvent(QResizeEvent *evt)
{
    //qDebug() << "resizeEvent changedSize:"  << changedSize ;

    changedSize = evt->size();

    QDialog::resizeEvent(evt);
}

void SizeRememberDlg::moveEvent(QMoveEvent *evt)
{
    //qDebug() << "moveEvent changedPos:"<< changedPos;

    changedPos = evt->pos();

    QDialog::moveEvent(evt);
}

void SizeRememberDlg::open()
{
    //qDebug() << "open changedSize:"  << changedSize << " changedPos :"<< changedPos;

    QDialog::open();
}

int SizeRememberDlg::exec()
{
    //originalSize = size();
    //originalRect = rect();

    restoreFromReestr();

    return QDialog::exec();
}
void SizeRememberDlg::done(int res)
{
    saveSizeAndPosToReestr( changedSize , changedPos ); // closeEvent не возникает

    QDialog::done(res);
}


bool SizeRememberDlg::restoreFromReestr()
{
    //qDebug() << "restoreFromReestr pathRect " <<pathRect;
    //qDebug() << "restoreFromReestr getMinimumSize() " <<getMinimumSize();
    //qDebug() << "minimumSize " <<minimumSize();

    if( pathRect.isNull() || pathPos.isNull())
        return false;

    if(  !getMinimumSize().isNull())
        setMinimumSize( getMinimumSize() );

    if( resizeStoreEnabled
            && reestr_settings.contains( pathRect )
            && reestr_settings.contains( pathPos )
            )
    {

        QRect rect = reestr_settings.value( pathRect ).toRect();
        setGeometry( rect );

        changedPos = reestr_settings.value( pathPos ).toPoint();
        move( changedPos );

    }
    return true;
}


bool SizeRememberDlg::saveSizeAndPosToReestr( const QSize & sz, const QPoint & pos )
{

    if( pathRect.isNull() || pathPos.isNull())
        return false;

    if( resizeStoreEnabled &&
            ( ! changedSize.isNull() || ! changedPos.isNull() )
            ) // было изменение
    {
        reestr_settings.setValue( pathRect , QRect ( pos , sz ) );
        reestr_settings.setValue( pathPos , pos );

    }

    return true;
}

//void SizeRememberDlg::enterEvent(QEvent* event) // mouse enters widget
//{

//    QDialog::enterEvent( event );
//    //event->accept();


//    // -------------------------------------------------------------------------------------------
//    // наличие QApplication::setOverrideCursor в enterEvent/leaveEvent
//    // влияет на появление на рамке возможности изменять размер
//    // и возникает именно перемещение окна , а не растягивание, конечно FramelessWindowHint отключен
//    // -------------------------------------------------------------------------------------------

//    //QApplication::setOverrideCursor( Qt::ForbiddenCursor);

//   // emit sig_updateCursor( Qt::PointingHandCursor );

//    //qDebug() << "enterEvent" <<QCursor::pos();//  << QApplication::overrideCursor()->shape();

//    //event->accept();
//}

//void SizeRememberDlg::leaveEvent( QEvent* event)
//{
//    //QApplication::changeOverrideCursor( Qt::ArrowCursor);
//    //unsetCursor();

//    QDialog::leaveEvent( event );
//    //event->accept();

//    QApplication::setOverrideCursor( Qt::ArrowCursor );

//    qDebug() << "leaveEvent"<< QCursor::pos();// << QApplication::overrideCursor()->shape();

//    //event->accept();

//    //emit sig_updateCursor( Qt::ArrowCursor );

//}


void SizeRememberDlg::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_mousePoint = event->pos();
        event->accept();
    }
}

void SizeRememberDlg::mouseMoveEvent(QMouseEvent* event)
{
    const QPointF delta = event->globalPos() - m_mousePoint;

    move(delta.toPoint());

    event->accept();
}
