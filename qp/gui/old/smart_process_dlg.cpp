#include "smart_process_dlg.h"
#include "ui_smart_process_dlg.h"

#include "my_gui/msg.h"


#include <QDesktopWidget>
#include <QDesktopServices>
#include <QDebug>
#include <QUrl>
#include <QScrollBar>

Smart_Process_Dlg * Smart_Process_Dlg::theStaticPointer =0;
Smart_Process_Dlg * Smart_Process_Dlg::dlg = 0;
QpSingleShotTimer * Smart_Process_Dlg::tmr = 0;

Smart_Process_Dlg::Smart_Process_Dlg( QWidget *receiverWgt,
                                      const QString &hdr,
                                      const QString &txt1,
                                      const QString &txt2,
                                      const QList<QObject*> &ObjLst
                                      )
    :
      QDialog(receiverWgt),
      ui(new Ui::Smart_Process_Dlg),
      res( false )

{
    ui->setupUi(this);

    ui->lbl_header->setText(hdr);
    ui->lbl_text1->setText(txt1);
    ui->lbl_text2->setText(txt2);

    ui->btn_wait->setVisible( false );


    foreach( QObject* obj , ObjLst)
    {
        bool bbb = connect( obj , SIGNAL( sig_finished(QString,bool)), this , SLOT( slot_finished(QString,bool)));

         if( ! bbb )
             Msg::mess( this ,
                        QString("ошибка создания связи сигнал sig_finished / слот slot_finished"));
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


    Q_ASSERT ( connect ( ui->lbl_text1 , SIGNAL(linkActivated(QString) ),
                         this , SLOT(slot_linkActivated(QString))) == true);


    Q_ASSERT ( connect ( ui->lbl_text2 , SIGNAL(linkActivated(QString) ),
                         this , SLOT(slot_linkActivated(QString))) == true);


    //ui->scrollArea->setWidgetResizable

    //---------------------- move to center ------------------------------

    int screenH = QApplication::desktop()->screenGeometry().height();
    int screenH_07 = (int)screenH *0.7;

    int AppFntHeight = QApplication::fontMetrics().height();

    int hh = qMin( screenH_07 , AppFntHeight * 30 );

    int screenW_05 = (int)hh *0.5;

    int ww = qMin( screenW_05 , AppFntHeight * 30 );


    QRect rectDlg( 0, 0, width(), height() );		// Window rectangle

    QPoint screenCenter = QApplication::desktop()->screenGeometry().center();

    QPoint to = screenCenter - rectDlg.center() ;
}

Smart_Process_Dlg::~Smart_Process_Dlg()
{
    delete ui;
}

void Smart_Process_Dlg::fooFunc()
{

}

bool Smart_Process_Dlg::call_slot( QWidget * receiverWgt,
                                   QObject * slotOwner,
                                   const QString & header,
                                   const QString &txt1 ,
                                   const QString &txt2,
                                   const QString &slot_name ,
                                   QList<QObject*> &senderList,
                                   const QList<QVariant>& pars
                                   )

{

    QApplication::setOverrideCursor(Qt::WaitCursor);

    dlg = new Smart_Process_Dlg( receiverWgt ,

                                 header,
                                 txt1,
                                 txt2,

                                 senderList

                                 );


    //theStaticPointer = dlg;
    if(theStaticPointer)
        theStaticPointer->fooFunc();


    tmr =  new QpSingleShotTimer( 200 ,
                                  slotOwner,
                                  slot_name,
                                  pars,
                                  receiverWgt ) ;

    if ( dlg->exec() == QDialog::Rejected ) //

        ;

    bool res = dlg->res;

    qWarning() << "msg2->exec(..) lbl2:" << dlg->lbl2;

    //tmr->killTimer();
    //delete tmr;
    delete dlg; // for static building

    dlg = 0;
    tmr = 0;

    return res;


}

void Smart_Process_Dlg::slot_finished( const QString &description ,
                                       bool error )
{

    int hh2 = ui->scrollAreaWidgetContents->height();
    int hh1 = ui->scrollArea->height();

    qWarning() <<"Smart_Process_Dlg::slot_finished"<<description << error;

    QString description2 = description;

    if( !description.isEmpty() )
        description2 = description2.replace(QLatin1String("\n"), QLatin1String("<br>"));

    if( ! description.isEmpty() ) // message or error
    {
        QString txt = ui->lbl_text2->text();

        txt.append("<p>"+description2+"</p>");

        txt = txt.replace(" ", "&nbsp;");

        ui->lbl_text2->setText( txt);


        //        int val = ui->scrollArea->horizontalScrollBar()->value();
        //        int max = ui->scrollArea->verticalScrollBar()->maximum();

        //        ui->scrollAreaWidgetContents->updateGeometry();
        //        int hh2 = ui->scrollAreaWidgetContents->height();
        //        int hh1 = ui->scrollArea->height();

        //        //ui->scrollArea->verticalScrollBar()->setSliderPosition( hh );
        //        //ui->scrollAreaWidgetContents->moveCursor();
        //        ui->scrollArea->ensureVisible( 0, hh2 );
        //        //ui->scrollArea->ensureWidgetVisible( )

        //        //ui->scrollArea->verticalScrollBar()->setValue( max + 5);

        //        qDebug() << "ui->scrollArea val " << val<< " max"<< max << " hh1" << hh1 << " hh2" << hh2;


        if( error )
        {
            QApplication::setOverrideCursor( Qt::ArrowCursor); //!!!
            //reject();
            res = false;
        }
        else
            ;//res = true;

        //update();
        //repaint();


    }
    else // str.isEmpty()
    {
        res = true;

        if( ! error )
        {
            QApplication::setOverrideCursor( Qt::ArrowCursor);
            repaint(); //!!
            lbl2 = ui->lbl_text2->text();
            qWarning() << "accept lbl2"<<lbl2;
            accept();
        }
    }

    repaint();


}

void Smart_Process_Dlg::slot_linkActivated(QString href)
{
    //qDebug() << "href " << href;

    QDesktopServices::openUrl( QUrl(href) );

}

void Smart_Process_Dlg::on_btn_Close_clicked()
{
    accept();
}
