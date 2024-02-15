#include "smart_process_dlg.h"
#include "ui_smart_process_dlg.h"

#include <QDesktopWidget>
#include <QDesktopServices>
#include <QDebug>
#include <QUrl>
#include <QScrollBar>
#include "../../qp/gui/qp_gui.h"
#include <QMetaMethod>
#include <QMessageBox>
#include "qp/qp.h"




Smart_Process_Dlg::Smart_Process_Dlg( QWidget *parent,
                                      QObject * SlotOwner,
                                      const QString &hdr,
                                      const QString &txt1,
                                      const QString &txt2,
                                      const QString &Slot_name ,
                                      const QList<QObject*> &ObjLst,
                                      const QList<QVariant>& Pars,
                                      bool CloseWindowOnFinished
                                      )
    :
      QDialog(parent),
      ui(new Ui::Smart_Process_Dlg),
      resInvokeMethod( false ),
      slot_name(Slot_name),
      pars( Pars),
      closeWindowOnFinished(CloseWindowOnFinished),
      tmr(0)


{
    ui->setupUi(this);

    slotOwner = SlotOwner;

    ui->lbl_header->setText(hdr);
    ui->lbl_text1->setText(txt1);
    ui->lbl_text2->setText(txt2);

    ui->btn_wait->setVisible( false );


    foreach( QObject* obj , ObjLst)
    {

        bool bbb = connect( obj , SIGNAL( sig_finished(QString,bool)), this , SLOT( slot_finished(QString,bool)));

        if( ! bbb )
            QMessageBox::critical( this ,
                                   "Error",
                                       QString("error: connecting signal(sig_finished ) / slot (slot_finished)")
                                   );

        bbb = connect( obj , SIGNAL( sig_log(QString , qp::gui::LOG_STYLE)),
                       this , SLOT( slot_log(QString , qp::gui::LOG_STYLE)));

        if( ! bbb )
            QMessageBox::critical( this ,
                                   "Error",
                                   QString("error: connecting signal(sig_log ) / slot (slot_log)")
                                   );
    }

    // -----------------------------------------------------------
    QApplication::setOverrideCursor(Qt::WaitCursor);


    tmr =  new QpSingleShotTimer( 200 ,
                                  slotOwner,
                                  slot_name,
                                  pars,
                                  parent ) ;

    if ( ! connect ( tmr , SIGNAL(sig_retResult(bool, QVariant)),
                          this , SLOT(slot_retResult(bool, QVariant))) )
    {
        QMessageBox::critical( this ,
                               "Error",
                               "connecting signal - slot is false");
        ;
    }

    // -----------------------------------------
    Qt::WindowFlags flags = windowFlags();

    flags &= ( ~Qt::WindowTitleHint );

    flags |= Qt::FramelessWindowHint;

    flags |= Qt::WindowMinMaxButtonsHint
            | Qt::WindowCloseButtonHint;


    setWindowFlags( flags );


    setAttribute(Qt::WA_TranslucentBackground );

    // -----------------------------------------


    ui->lbl_header->setTextInteractionFlags(Qt::TextSelectableByMouse);

    ui->lbl_text1->setTextInteractionFlags(Qt::TextSelectableByMouse);

    ui->lbl_text2->setTextInteractionFlags(Qt::TextSelectableByMouse);


    QP_ASSERT ( connect ( ui->lbl_text1 , SIGNAL(linkActivated(QString) ),
                          this , SLOT(slot_linkActivated(QString))) == true);


    QP_ASSERT ( connect ( ui->lbl_text2 , SIGNAL(linkActivated(QString) ),
                          this , SLOT(slot_linkActivated(QString))) == true);


    //---------------------- move window to center ------------------------------

    int screenH = QApplication::desktop()->screenGeometry().height();
    int screenH_07 = (int)screenH *0.7;

    int AppFntHeight = QApplication::fontMetrics().height();

    int hh = qMin( screenH_07 , AppFntHeight * 30 );

    int screenW_05 = (int)hh *0.5;

    int ww = qMin( screenW_05 , AppFntHeight * 30 );


    QRect rectDlg( 0, 0, width(), height() );		// Window rectangle

    QPoint screenCenter = QApplication::desktop()->screenGeometry().center();

    QPoint to = screenCenter - rectDlg.center() ;


    QP_ASSERT( connect( ui->scrollArea->verticalScrollBar(), SIGNAL( rangeChanged(int,int) ),
               this, SLOT(slot_rangeChanged(int,int)) )== true);

}

void Smart_Process_Dlg::slot_rangeChanged(int min ,int max)
{
    qDebug()<< "slot_rangeChanged min" <<min<<" max"<<max;

    if( max >0 )
        ui->scrollArea->verticalScrollBar()->setValue( max );
}


void Smart_Process_Dlg::slot_retResult(bool ResInvokeMethod, const QVariant& RetValue)
{
    retVal = RetValue;
    resInvokeMethod = ResInvokeMethod;


    if( ! resInvokeMethod )
    {

        const QMetaObject* metaObject = slotOwner->metaObject();

        QStringList methods;

        bool foundMethodName = false;

        for(int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i)
        {
            if( QString::fromLatin1(metaObject->method(i).signature()) == slot_name)
                foundMethodName = true;
        }

        if( ! foundMethodName )
        {
            QApplication::setOverrideCursor( Qt::ArrowCursor );


            QMessageBox::warning( this ,
                                  "Error",
                                  QString("Object has not a slot '%1'.")
                                  .arg(slot_name )
                                  );

            return;
        }

        QString pp;

        foreach( QVariant var, pars )
        {
            if(! pp.isEmpty())
                pp.append(QLatin1String(","));

            pp.append( var.typeName());
        }

        QApplication::setOverrideCursor( Qt::ArrowCursor );

        QMessageBox::warning( this ,
                              "Ошибка",
                              QString("некорректные параметры передаются в слот  '%1(%2)' , также тип возвращаемого значения должен быть QVariant.")
                              .arg(slot_name )
                              .arg( pp )
                              );
    }
}

bool Smart_Process_Dlg::getInvokeMethodResult()
{
    return resInvokeMethod;
}

QVariant Smart_Process_Dlg::getRetValue()
{
    return retVal;
}

Smart_Process_Dlg::~Smart_Process_Dlg()
{
    delete ui;
}



void Smart_Process_Dlg::slot_finished( QString description ,
                                       bool error )
{

    //qWarning() <<"Smart_Process_Dlg::slot_finished"<<description << error;

    // -------------------------------------------------------
    //  finished process execute
    // -------------------------------------------------------

    if( ! description.isEmpty() ) // message
    {
        QString description2 = description;
        description2 = description2.replace(QLatin1String("\n"), QLatin1String("<br>"));

        description2 = description2.replace(" ", "&nbsp;");

        QString txt = ui->lbl_text2->text();

        txt.append("<p>"+description2+"</p>");

        ui->lbl_text2->setText( txt);

        repaint();

    }

    QApplication::setOverrideCursor( Qt::ArrowCursor); //!!!

    if( error )
    {
        // window still is opened on display
    }
    else
    {
        if ( closeWindowOnFinished )
            accept();
    }

}

void Smart_Process_Dlg::slot_log( const QString &description , qp::gui::LOG_STYLE style )
{

    //qWarning() <<"Smart_Process_Dlg::void Smart_Process_Dlg::slot_log( const QString &description , qp::gui::LOG_STYLE style ) "<<description << error;


    if( ! description.isEmpty() ) // message or error
    {
        QString description2 = description;

        description2 = description2.replace(QLatin1String("\n"), QLatin1String("<br>"));

        description2 = description2.replace(" ", "&nbsp;");

        QString txt = ui->lbl_text2->text();

        txt.append("<p style=\""+ qp::gui::styleToHtmlAttr( style ) +"\">"+description2+"</p>");


        ui->lbl_text2->setText( txt);

        repaint();

    }
}

void Smart_Process_Dlg::slot_linkActivated(QString href)
{
    //qDebug() << "href " << href;

    QDesktopServices::openUrl( QUrl(href) );

}

void Smart_Process_Dlg::on_btn_Close_clicked()
{
    QApplication::setOverrideCursor( Qt::ArrowCursor);
    accept();
}
