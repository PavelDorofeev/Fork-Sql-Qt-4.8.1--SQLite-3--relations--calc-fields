#include "sizerememberdlg.h"
//#include "ui_sizerememberdlg.h"

#include <QDebug>
#include <QApplication>
#include <QMessageBox>
#include <QResizeEvent>
#include "qp/qp.h"

SizeRememberDlg::SizeRememberDlg( QWidget *parent )
    :
      QDialog(parent),
      //uiSzDlg(new Ui::SizeRememberDlg),

      reestTreeName(QApplication::organizationName()),
      reestrName(QApplication::applicationName()),
      resizeStoreEnabled( false ),
      changedSize(QSize()),
      changedPos(QPoint()),
      pathRect(QString()),
      pathPos(QString())

{
    //uiSzDlg->setupUi(this);

    /*

     ВАЖНО : В КОНСТРУКТОРЕ НЕ ВЫЗЫВАЮТСЯ ВИРТУАЛЬЬНЫЕ ФУНКЦИИ
     поэтому init()
     */


    if( QApplication::organizationName().isEmpty() || QApplication::applicationName().isEmpty())
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

    setMouseTracking( true );

}

void SizeRememberDlg::init()
{
    /*

     ВАЖНО : В КОНСТРУКТОРЕ НЕ ВЫЗЫВАЮТСЯ ВИРТУАЛЬНЫЕ ФУНКЦИИ
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
      НЕ СМОТРЯ на ui наследника
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

//void SizeRememberDlg::focusInEvent(QFocusEvent * evt) // keyboard focus received
//{
//    qDebug() << "focusOutEvent reason" << evt->reason();

//    QDialog::focusInEvent(evt);
//}

//void SizeRememberDlg::focusOutEvent(QFocusEvent * evt)
//{
//    qDebug() << "focusOutEvent reason" << evt->reason();

//    QDialog::focusOutEvent(evt);
//}

//bool SizeRememberDlg::event(QEvent *evt)
//{
//    qDebug() <<  "oname"<< objectName() << qp::dbg::toStr_Event_Type( evt->type());

//    return QDialog::event( evt);

//}

//void SizeRememberDlg::enterEvent(QEvent* event) // mouse enters widget
//{

//    QDialog::enterEvent( event );


//    QApplication::setOverrideCursor( Qt::ForbiddenCursor);//Qt::SizeAllCursor);

//   // emit sig_updateCursor( Qt::PointingHandCursor );

//    //setCursor( curs2 ); // не работает
//    //setMouseTracking(true);

//    qDebug() << "enterEvent" <<QCursor::pos();//  << QApplication::overrideCursor()->shape();

//    //event->accept();
//}

//void SizeRememberDlg::leaveEvent( QEvent* event)
//{
//    //QApplication::changeOverrideCursor( Qt::ArrowCursor);
//    //unsetCursor();

//    QDialog::leaveEvent( event );

//    //    QApplication::changeOverrideCursor( Qt::ArrowCursor);
//    //    QApplication::changeOverrideCursor( Qt::ArrowCursor);

//    QApplication::setOverrideCursor( Qt::ArrowCursor );

//    qDebug() << "leaveEvent"<< QCursor::pos();// << QApplication::overrideCursor()->shape();

//    //event->accept();

//    //emit sig_updateCursor( Qt::ArrowCursor );

//}

//void SizeRememberDlg::slot_updateCursor( int curs)
//{
//    Qt::CursorShape cursotType =(Qt::CursorShape) curs;

//    QApplication::setOverrideCursor( cursotType );

//    qDebug() << "slot_updateCursor"<< QCursor::pos() << QApplication::overrideCursor()->shape();

//    //parentWidget()->
//    QApplication::processEvents();
//    update();
//    QApplication::processEvents();

//}

//void SizeRememberDlg::moveEvent(QMoveEvent *evt)
//{
//    qDebug() << "moveEvent changedPos : "<< changedPos;

//    changedPos = evt->pos();

//    QDialog::moveEvent(evt);
//    //event->accept();
//}

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

//QString SizeRememberDlg::getReestrPrefix() const
//{
//    return "SizeRememberDlg";
//}

void SizeRememberDlg::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_mousePoint = event->pos();
        event->accept();
    }
}

void SizeRememberDlg::mouseMoveEvent(QMouseEvent* evt)
{
    const QPointF delta = evt->globalPos() - m_mousePoint;

    qDebug() << "mouseMoveEvent" << evt->globalPos();

    move( delta.toPoint() );

    evt->accept();
}


